#include "airship.h"
#include "engine.h"
#include <stdlib.h>

//Thread safety / Limites :
//seul pb non protégé par le code : destroy_engines/destroy_airship après le join de tous les threads seulement => pas d'appelants tjrs en train de modif
//sinon l'entiereté du code est thread safe en parallele

struct airship *init_airship(size_t capacity, int fuel, int ammunition,int health, size_t nb_cannons){
	if(nb_cannons<1 || nb_cannons>4 || capacity==0 || health<=0 || fuel<0 || ammunition<0) return NULL;
	struct airship *ship = malloc(sizeof(struct airship));
	if(!ship) return NULL;
	struct crew *c = malloc(sizeof(struct crew));
	if(!c) {free(ship);return NULL;}
	ship->crew = c;
	ship->crew->crew_capacity = capacity;
	ship->crew->crew_count = 0;
	char **m = malloc(capacity*sizeof(char *));
	if(!m) {free(ship);free(c);return NULL;}
	ship->crew->members = m;
	for(size_t i=0; i < capacity; i++){ship->crew->members[i]=NULL;}
	ship->fuel = fuel; 
	ship->ammunition = ammunition;
	ship->health = health; 
	ship->max_health = health;
	ship->nb_cannons = nb_cannons;
	ship->nb_engine = 0;
	ship->engines = NULL;
	if(sem_init(&ship->cannon_slots, 0, nb_cannons)!=0) {free(ship);free(c);free(m);return NULL;}
	if(pthread_mutex_init(&ship->mutex, NULL)!=0){sem_destroy(&ship->cannon_slots);free(ship);free(c);free(m);return NULL;}
	if(pthread_cond_init(&ship->engine_cond, NULL)!=0){
		sem_destroy(&ship->cannon_slots);
		pthread_mutex_destroy(&ship->mutex);
		free(ship);free(c);free(m);return NULL;
	}
	return ship;
}

void destroy_airship(struct airship *ship){
	if(ship){
		for(size_t i=0; i<ship->crew->crew_count; i++){free(ship->crew->members[i]);}
		free(ship->crew->members); free(ship->crew);
		destroy_engines(ship);
		sem_destroy(&ship->cannon_slots);
		pthread_mutex_destroy(&ship->mutex);
		pthread_cond_destroy(&ship->engine_cond);
		free(ship);
	}
}

