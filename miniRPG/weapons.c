#include "weapons.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct gun *init_gun(char name[50], int damage, enum distance range, int magazine_size){
	struct gun *gun = malloc(sizeof(struct gun)); if(!gun) return NULL;
	strcpy(gun->name, name);
	gun->damage = damage;
	gun->range = range;
	gun->magazine_size = magazine_size;
	gun->current_magazine = magazine_size;
	return gun;
}

void reload(struct gun *gun){
	if(gun) gun->current_magazine = gun->magazine_size;
}

void destroy_gun(struct gun *gun){
	if(gun) free(gun);
}