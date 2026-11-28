#include "update_crew.h"
#include <stdlib.h>

//Thread safety :
//update_crew tient ship->mutex pendant toute la séquence (recherche + écriture) => atomique
//si recherche et écriture n'étaient pas atomiques => des threads en concurrence pourraient ajouter des doublons, use-after-free, etc.
//mais recherche + ecriture en atomique rend chaque thread couteuse en temps finalement
//add_pirate/remove_pirate verrouillent le mutex (utilisables seules) ; add_locked/remove_locked sont la même logique sans lock,
//appelées par update_crew qui tient déjà le mutex (non récursif => sinon deadlock)
//find_pirate_worker sans lock : lecteur seul, pas de modif, il ne tourne que pendant que update_crew tient le mutex (sinon deadlock au join)

//Limites : 
//pas de check malloc ou thread create/join

size_t crew_strlen(const char *str){
	size_t k=0;
	while(str[k]) k++;
	return k;
}

int crew_strcmp(const char *s1, const char *s2){
	while(*s1 && (*s1 == *s2)) {s1++;s2++;}
	return (unsigned char)*s1 - (unsigned char)*s2;
}
char *crew_strcpy(char *dest, const char *src){
	int k=0;
	while(src[k]) {dest[k] = src[k]; k++;}
	dest[k]='\0';
	return dest;
}

void add_locked(struct crew_args *a){
	if(a->ship->crew->crew_count < a->ship->crew->crew_capacity){
		size_t l = crew_strlen(a->name);
		a->ship->crew->members[a->ship->crew->crew_count] = malloc(l+1);
		crew_strcpy(a->ship->crew->members[a->ship->crew->crew_count], a->name);
		a->ship->crew->crew_count++;
	}
}

void remove_locked(struct crew_args *a){
	for (size_t i = 0; i < a->ship->crew->crew_count; i++){
		if(crew_strcmp(a->ship->crew->members[i], a->name) == 0){
			free(a->ship->crew->members[i]);
			for (size_t j = i; j < a->ship->crew->crew_count -1; j++){
				a->ship->crew->members[j] = a->ship->crew->members[j+1];
			}
			a->ship->crew->crew_count--;
			a->ship->crew->members[a->ship->crew->crew_count] = NULL;
			break;
		}
	}
}

void *add_pirate(void *arg){
	struct crew_args *a = arg;
	pthread_mutex_lock(&a->ship->mutex);
	add_locked(a);
	pthread_mutex_unlock(&a->ship->mutex);
	return NULL;
}

void *remove_pirate(void *arg){
	struct crew_args *a = arg;
	pthread_mutex_lock(&a->ship->mutex);
	remove_locked(a);
	pthread_mutex_unlock(&a->ship->mutex);
	return NULL;
}

void *find_pirate_worker(void *arg){
	struct crew_search_args *a = arg;
	for(size_t i=0; i<a->crew->crew_count;i++) if(crew_strcmp(a->crew->members[i], a->name) == 0) {a->found=1;break;}
	return NULL;
}

int update_crew(struct airship *ship, const char **names, size_t n){
	if(!ship || !ship->crew) return 42;
	if(n==0) return 0;
	if(!names) return 42;
	for(size_t i=0; i < n;i++) if(!names[i]) return 42;
	pthread_t pt[n];
	struct crew_search_args arg[n];
	pthread_mutex_lock(&ship->mutex);
	for(size_t i=0; i < n;i++) {
		arg[i].crew = ship->crew;
		arg[i].name = names[i];
		arg[i].found = 0;
		pthread_create(&pt[i], NULL, find_pirate_worker, &arg[i]);
	}
	for(size_t i=0; i < n;i++) pthread_join(pt[i], NULL);
	for(size_t i=0; i < n;i++) {
		struct crew_args a;
		a.ship = ship;
		a.name = names[i];
		a.error = 0; //arg if we want to check some stuff worked as intended (ex malloc or pthread_join didnt fail etc)
		if(arg[i].found==1) remove_locked(&a);
		else add_locked(&a);
	}
	pthread_mutex_unlock(&ship->mutex);
	return 0;
}

