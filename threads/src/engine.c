#include "engine.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NB 2

//Thread safety :
//init_engines :
//malloc et remplissage hors lock car e est local, pas encore partagé
//test (engines != NULL) + affectation dans la meme section critique : deux init concurrents => un seul réussit, l'autre libere son tableau et renvoie 42
//start_engine (worker) :
//test et working++ dans la meme section critique, sinon deux opé verraient "1" en meme temps et on passerait à 3
//fuel -= est un read-write non atomique => donc doit etre sous mutex
//sleep(1) simulate work mais hors section critique ici attention
//start_engines :
//engines et nb_engine lus sous mutex car init/start peuvent tourner en parallele
//le trou entre les deux locks c pas un pb => refait la verif et la réservation de facon atomique apres
//par ex si un autre start_engines est appelé entre temps, il a deja mis started = 1 => on renvoie 42
//réservation (started = 1) dans la meme section critique que la verif => pas de double démarrage => pas de carburant négatif par ex
//started = 1 est posé dès la réservation pour pouvoir etre thread safe avec plusieurs appelants en parallele
//mutex unlock avant create/join => les workers en ont besoin (sinon deadlock)

int init_engines(struct airship *ship, const int *requirements, size_t n){
	if(!ship || n==0 || !requirements) return 42;
	for(size_t i=0; i < n; i++) if(requirements[i]<=0) return 42;
	struct engine *e = malloc(n*sizeof(struct engine));
	if(!e) return 42;
	for(size_t i=0; i < n; i++){
		e[i].required_fuel=requirements[i];
		e[i].started=0;
	}
	pthread_mutex_lock(&ship->mutex);
	if(ship->engines){pthread_mutex_unlock(&ship->mutex);free(e);return 42;}
	ship->nb_engine=n;
	ship->engines = e;
	pthread_mutex_unlock(&ship->mutex);
	return 0;
}

void *start_engine(void *arg){
	struct engine_args *a = arg;
	pthread_mutex_lock(&a->ship->mutex);
	while (*a->working >= NB) pthread_cond_wait(&a->ship->engine_cond, &a->ship->mutex);
	(*a->working)++;
	a->ship->fuel -= a->engine->required_fuel;
	pthread_mutex_unlock(&a->ship->mutex);
	sleep(1); // simulate work, hors section critique
	pthread_mutex_lock(&a->ship->mutex);
	a->engine->started = 1;
	(*a->working)--;
	pthread_cond_signal(&a->ship->engine_cond);
	pthread_mutex_unlock(&a->ship->mutex);
	return NULL;
}

int start_engines(struct airship *ship){
	if(!ship) return 42;
	pthread_mutex_lock(&ship->mutex);
	if(!ship->engines || ship->nb_engine == 0) {pthread_mutex_unlock(&ship->mutex);return 42;}
	pthread_mutex_unlock(&ship->mutex);
	pthread_t pt[ship->nb_engine];
	struct engine_args a[ship->nb_engine];
	int tot=0;
	pthread_mutex_lock(&ship->mutex);
	for (size_t i = 0; i < ship->nb_engine; i++) {
		if(ship->engines[i].started) {pthread_mutex_unlock(&ship->mutex);return 42;}
		else tot+=ship->engines[i].required_fuel;
	}
	if(ship->fuel < tot){pthread_mutex_unlock(&ship->mutex);return 42;}
	for (size_t i = 0; i < ship->nb_engine; i++) ship->engines[i].started = 1;
	pthread_mutex_unlock(&ship->mutex);
	size_t w = 0;
	int cnt=0,err=0;
	for (size_t i = 0; i < ship->nb_engine; i++){
		a[i].ship = ship;
		a[i].engine = &ship->engines[i];
		a[i].working = &w;
		if(pthread_create(&pt[i], NULL, start_engine, &a[i])){err=42;break;}
		cnt++;
	}
	for (size_t i = 0; i < cnt; i++) if(pthread_join(pt[i], NULL)) err=42;
	return err;
}

void destroy_engines(struct airship *ship){
	if(ship){
		free(ship->engines);
		ship->engines = NULL;
		ship->nb_engine = 0;
	}
}

