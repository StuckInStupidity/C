#include "cannon.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int cannon_hit(void){return rand() % 100 < 75;}

int shoot(struct airship *ship, struct airship *enemy){
	if(!ship || !enemy || ship==enemy) return 42;
	if(pthread_mutex_lock(&ship->mutex)) return 42;
	if(pthread_mutex_lock(&enemy->mutex)) {pthread_mutex_unlock(&ship->mutex);return 42;}
	if(ship->ammunition == 0 || enemy->health <= 0) {pthread_mutex_unlock(&enemy->mutex);pthread_mutex_unlock(&ship->mutex);return -1;}
	ship->ammunition--;
	if(cannon_hit()) {enemy->health -= 10; if(enemy->health<0) enemy->health=0;}
	int mute = pthread_mutex_unlock(&enemy->mutex);
	int muta = pthread_mutex_unlock(&ship->mutex);
	if(mute || muta) return 42;
	return 0;
}

void *fire_cannon(void *arg){
	struct cannon_args *a = arg;
	while((a->result=sem_wait(&a->ship->cannon_slots)) && errno == EINTR);
	if(a->result){a->result = 42;return NULL;}
	int s = shoot(a->ship, a->enemy);
	if(s==0) sleep(1);
	if(sem_post(&a->ship->cannon_slots)){a->result = 42; return NULL;}
	if(s==42) a->result=42;
	else a->result=0;
	return NULL;
}

int fire_cannons(struct airship *ship,struct airship *enemy,size_t nb_shots){
	if(!ship || !enemy || ship == enemy || !ship->crew || ship->nb_cannons < 1 || ship->nb_cannons > 4) return 42;
	size_t mini = 4;
	if(nb_shots < mini) mini = nb_shots;
	if(pthread_mutex_lock(&ship->mutex)) return 42;
	if(ship->crew->crew_count < mini) mini = ship->crew->crew_count;
	if(pthread_mutex_unlock(&ship->mutex)) return 42;
	if(mini==0) return 0;
	pthread_t pt[mini];
	struct cannon_args a[mini];
	int err=0,cnt=0;
	for(size_t i=0;i<mini;i++){
		a[i].ship = ship;
		a[i].enemy = enemy;
		a[i].result = 0;
		if(pthread_create(&pt[i], NULL, fire_cannon, &a[i])) {err=42;break;}
		cnt++;
	}
	for(int i=0;i<cnt;i++) {
		if(pthread_join(pt[i],NULL)) err = 42;
		else if(a[i].result) err=42;
	}
	return err;
}

