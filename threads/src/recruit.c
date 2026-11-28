#include "recruit.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Thread safety : 
//Aucune donnée partagée, chaque thread a son propre id et printf est thread-safe
//attention : les threads étant détachés, rien ne garantit qu’elles aient fini avant la fin du programme

void *aux(void *arg){
	int *id = arg;
	printf("Pirate %d wants to join!\n", *id);
	free(id);
	return NULL;
}

int recruit_pirates(int n){
	if(n<0) return 42;
	for(int i=0; i<n;i++) {
		int *id = malloc(sizeof(int));
		if(!id) return 42;
		*id = i+1;
		pthread_t t;
		if(pthread_create(&t,NULL,aux,id)!=0){free(id);return 42;} //&i => share same variable for all threads => race condition
		if(pthread_detach(t)!=0) return 42;
	}
	return 0;
}