#include "animals.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct insect *insect_init(const char *species, size_t size, int can_fly, int can_swim){
	if(!species) return NULL;
	struct insect *i = malloc(sizeof(struct insect));if(!i) return NULL;
	i->species = strdup(species);if(!i->species) {free(i); return NULL;}
	i->can_fly = can_fly;i->size = size;i->can_swim = can_swim;
	return i;
}

struct animal *animal_from_insect(const char *color, struct insect *insect){
	if(!color || !insect) return NULL;
	struct animal *ai = malloc(sizeof(struct animal));if(!ai) return NULL;
	ai->type = INSECT;
	ai->color = strdup(color);if(!ai->color) {free(ai);return NULL;}
	ai->animal.insect = insect;
	return ai;
}

void free_insect(struct insect *insect){
	if(insect) {free(insect->species);free(insect);}
}
