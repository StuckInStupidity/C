#include "supplies.h"
#include <stdio.h>
#include <stdlib.h>

//Thread safety :
//Le mutex protège bien fuel++, qui est un opération de read-write non atomique
//sinon deux threads pourrait obtenir le même compteur et on perdrait un incrément
//ici pas besoin de lock toute la boucle cela n'affectera pas le resultat attendu dans notre cas

void *load_worker(void *arg){
	struct load_args *a = arg;
	// or protect the loop directly or increment amount directly
	for(int i=0; i<a->amount;i++){
		pthread_mutex_lock(&a->ship->mutex);
		a->ship->fuel++;
		//we can add a printf and an id with the args to see which thread is implementing and when
		pthread_mutex_unlock(&a->ship->mutex);
	}
	return NULL;
}

int load_supplies(struct airship *ship, int n, int amount){
	if(ship == NULL || n < 0 || amount < 0) return 42;
	if(n == 0 || amount == 0) return 0;
	pthread_t pt[n];
	struct load_args a[n];
	int err=0, cnt=0;
	for(int i=0;i<n;i++){
		a[i].ship=ship;
		a[i].amount=amount;
		if(pthread_create(&pt[i], NULL, load_worker, &a[i])){err=42;break;}
		cnt++;
	}
	for(int i=0; i<cnt; i++) if(pthread_join(pt[i], NULL)) err=42;
	return err;
}
