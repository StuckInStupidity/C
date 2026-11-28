//Résolution du problème des philosophes
#define N 5
#define GAUCHE (i+N-1)%N
#define DROITE (i+1)%N
#define PENSE 0
#define FAIM 1
#define MANGE 2

typedef int semaphore; //Les sémaphores sont des int spéciaux
int state[N];
semaphore mutex = 1;
semaphore s[N];
void philosophe(int i) {
	while (true) {
		penser();
		prendre_fourchettes(i);
		manger();
		poser_fourchettes(i);
	}
}
void prendre_fourchettes(int i) {
	down(&mutex);
	state[i] = FAIM;
	test(i);
	up(&mutex);
	down(&s[i]);
}
void poser_fourchettes(i) {
	down(&mutex);
	state[i] = PENSE;
	test(GAUCHE);
	test(DROITE);
	up(&mutex);
}
void test(i) {
	if (state[i] == FAIM && state[GAUCHE] != MANGE && state[DROITE] != MANGE) {
		state[i] = MANGE;
		up(&s[i]);
	}
}




//Résolution du problème des lecteurs et des rédacteurs
typedef int semaphore;
semaphore db = 1;
semaphore mutex = 1;
int rc = 0;
void reader(void) {
	while (true) {
		down(&mutex);
		rc += 1;
		if (rc == 1) down(&db);
		up(&mutex);
		read_data_base();
		down(&mutex);
		rc -= 1;
		if (rc == 0) up(&db);
		up(&mutex);
		use_data_read();
	}
}
void writer(void) {
	while (true) {
		think_up_data();
		down(&db);
		write_data_base();
		up(&db);
	}
}




//Producteur-consommateur

#include<pthread.h>
#include<stdio.h>
#define MAX 1000000
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer=0;

void *producer(void *ptr){
	int i;
	for(i=1; i<=MAX; i++){
		pthread_mutex_lock(&the_mutex);  // acces exclusif au tampon
		while(buffer != 0) pthread_cond_wait(&condp, &the_mutex); // endort le producteur
		buffer = i;
		pthread_cond_signal(&condc); // reveille le consommateur
		pthread_mutex_unlock(&the_mutex); // lache le tampon
	}
	pthread_exit(0);
}

void *consumer(void *ptr){  // consommation des donnees
	int i;
	for(i=1; i<=MAX; i++){
		pthread_mutex_lock(&the_mutex); // acces exclusif au tampon
		while(buffer == 0) pthread_cond_wait(&condc, &the_mutex); // endort le consommateur
		buffer = 0;
		pthread_cond_signal(&condp); // reveille le producteur
		pthread_mutex_unlock(&the_mutex); // lache le tampon	
	}
	pthread_exit(0);
}

int main(int argc, char **argv){
	pthread_t pro, con;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
}

/*
pthread_cond_wait() libère automatiquement le mutex puis endort le thread jusqu’à ce qu’un signal réveille la condition
et lorsqu’il se réveille il ré-acquiert le mutex avant de continuer, ce qui permet une synchronisation propre entre threads
l’utilisation d’un while autour de pthread_cond_wait() est indispensable pour retester la condition après un réveil concurrent
*/

//pthread_barrier_wait(&barrier); ex of a sync tool also

