#include "animals.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct fish *fish_init(const char *species, int speed, size_t size, int fresh_water){
	if(species==NULL) return NULL;
	struct fish *ff = malloc(sizeof(struct fish));if(!ff) return NULL;
	ff->species = strdup(species);if(!ff->species) {free(ff); return NULL;}
	ff->swimming_speed = speed;ff->size = size;ff->lives_in_fresh_water = fresh_water;
	return ff;
}

struct animal *animal_from_fish(const char *color, struct fish *fish){
	if(!color || !fish) return NULL;
	struct animal *af = malloc(sizeof(struct animal));if(!af) return NULL;
	af->type = FISH;
	af->color = strdup(color);if(!af->color) {free(af);return NULL;}
	af->animal.fish = fish;
	return af;
}

void free_fish(struct fish *fish){
	if(fish) {free(fish->species);free(fish);}
}