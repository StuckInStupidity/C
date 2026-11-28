#include "include/airship.h"
#include "include/engine.h"
#include "include/supplies.h"
#include "include/update_crew.h"
#include <stdio.h>

#define CREW_CAPACITY 5
#define FUEL 40
#define AMMUNITION 10
#define HEALTH 100
#define CANNONS 4
#define NB_THREADS 3
#define ADD_FUEL 20

//add scanf for entertainement

int main(void){
	struct airship *ship = init_airship(CREW_CAPACITY, FUEL, AMMUNITION, HEALTH, CANNONS);
	const char *team[] = {"Pazu","Louis","Dora"};
	if(update_crew(ship,team,3)) {destroy_airship(ship);return 42;}
	if(load_supplies(ship,NB_THREADS,ADD_FUEL)) {destroy_airship(ship);return 42;}
	const int req[] = {10,20,30,40};
	if(init_engines(ship,req,4)) {destroy_airship(ship);return 42;}
	if(start_engines(ship)) {destroy_airship(ship);return 42;}
	int cnt=0;
	for(size_t i=0; i<ship->nb_engine; i++) if(ship->engines[i].started) cnt++;
	printf("Crew: %zu/%zu\n", ship->crew->crew_count, ship->crew->crew_capacity);
	printf("Engines started: %d/%zu\n", cnt, ship->nb_engine);
	printf("Remaining fuel: %d\n", ship->fuel);
	destroy_airship(ship);
	return 0;
}