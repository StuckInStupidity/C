#include "vector.h"
#include "animals.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct vector *vector_init(size_t n){
	struct vector *v = malloc(sizeof(struct vector));if(!v) return NULL;
	v->animal = malloc(sizeof(struct animal*)*n);if(!v->animal){free(v);return NULL;}
	v->capacity = n;
	v->size = 0;
	return v;	
}

struct vector *vector_resize(struct vector *v, size_t new_capacity){
	if(!v) return NULL;
	v->animal = realloc(v->animal, sizeof(struct animal*)*new_capacity);if(!v->animal){free(v);return NULL;}
	v->capacity = new_capacity;
	return v;
}

struct vector *vector_append(struct vector *v, struct animal *animal){
	if(!v || !animal) return NULL;
	if(v->size == v->capacity) v = vector_resize(v, v->capacity*2);if(!v) return NULL;
	v->size++;(v->animal)[v->size - 1] = animal;
	return v;
}

void free_animal(struct animal *animal){
	if(animal){
		if(animal->type==FISH) free_fish(animal->animal.fish);
		else if(animal->type==INSECT) free_insect(animal->animal.insect);
		free(animal->color);free(animal);
	}
}

void vector_destroy(struct vector *v){
	if(v){for(size_t i=0; i<v->size; i++) if(v->animal && v->animal[i]) free_animal(v->animal[i]);if(v->animal) free(v->animal);free(v);}
}