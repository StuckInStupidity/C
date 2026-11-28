#include "wait_pirates.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Thread safety : 
//Aucune donnée partagée, chaque thread a son propre id et printf est thread-safe
//pthread join is sufficient as a synchronisation tool

int prime(int n){
	if(n<2) return 0;
	for(int i=2;i*i<=n;i++) {if(n%i==0) return 0;}
	return 1;
}

void *check_pirate(void *arg){
	int *id = arg;
	if(prime(*id)) printf("Pirate %d joined the crew!\n", *id);
	free(id);
	return NULL;
}

int wait_for_pirates(int n){
	if(n<0) return 42;
	if(n==0) {printf("All pirates have been checked!\n");return 0;}
	pthread_t pt[n];
	int err=0, cnt=0;
	for(int i=0; i<n;i++) {
		int *id = malloc(sizeof(int));
		if(!id){err=42;break;}
		*id = i;
		if(pthread_create(&pt[i],NULL,check_pirate,id)){free(id);err=42;break;}
		cnt++;
	}
	for(int i=0; i<cnt;i++) if(pthread_join(pt[i], NULL)) err=42;
	if(err) return err;
	printf("All pirates have been checked!\n");
	return 0;
}