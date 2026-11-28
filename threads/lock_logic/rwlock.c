#include <pthread.h>
#include <stdlib.h>
#include "rwlock.h"

struct rwlock *rwlock_init(void){
	struct rwlock *n = malloc(sizeof(struct rwlock));
	n->read_nb = 0;
	pthread_mutex_init(&n->internal, NULL);
	pthread_mutex_init(&n->write, NULL);
	return n;
}

int rwlock_destroy(struct rwlock *rwlock){
	if(!rwlock) return 1;
	if(pthread_mutex_destroy(&rwlock->internal)!=0) return 1;
	if(pthread_mutex_destroy(&rwlock->write)!=0) {pthread_mutex_init(&rwlock->internal, NULL);return 1;}
	free(rwlock);
	return 0;
}

int rwlock_request_read(struct rwlock *rwlock){
	if(!rwlock) return 1;
	if(!pthread_mutex_lock(&rwlock->internal)) {
		if(rwlock->read_nb == 0 && pthread_mutex_lock(&rwlock->write)){
			pthread_mutex_unlock(&rwlock->internal);
			return 1;
		}
		rwlock->read_nb++;
		pthread_mutex_unlock(&rwlock->internal);
		return 0;
	}
	return 1;	
}

int rwlock_end_read(struct rwlock *rwlock){
	if(!rwlock) return 1;
	if(!pthread_mutex_lock(&rwlock->internal)) {
		//to check it is not called more times but a test <= 0 inside the else should be enough if it was int not size_t
		if(rwlock->read_nb == 0) {pthread_mutex_unlock(&rwlock->internal); return 1;}
		else {
			rwlock->read_nb--;
			if(rwlock->read_nb == 0) pthread_mutex_unlock(&rwlock->write);
			pthread_mutex_unlock(&rwlock->internal);
			return 0;
		}
	}
	return 1;	
}

int rwlock_request_write(struct rwlock *rwlock){
	if(!rwlock) return 1;
	if(pthread_mutex_lock(&rwlock->write)) return 1;
	return 0;
}

int rwlock_end_write(struct rwlock *rwlock){
	if(!rwlock) return 1;
	pthread_mutex_unlock(&rwlock->write);
	return 0;
}

