#ifndef ANIMALS_H
#define ANIMALS_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

enum animal_type
{
    INSECT,
    FISH,
};

struct fish
{
    char* species;
    int swimming_speed;
    size_t size;
    int lives_in_fresh_water;
};

struct insect
{
    char* species;
    size_t size;
    int can_fly;
    int can_swim;
};

union animals
{
    struct insect* insect;
    struct fish* fish;   
};

struct animal
{
    enum animal_type type;
    union animals animal;
    char* color; 
};

struct fish* fish_init(const char* species, int speed, size_t size, int fresh_water);
struct animal* animal_from_fish(const char* color, struct fish* fish);
void free_fish(struct fish* fish);
struct insect *insect_init(const char *species, size_t size, int can_fly, int can_swim);
struct animal* animal_from_insect(const char* color, struct insect* insect);
void free_insect(struct insect* insect);
void free_animal(struct animal* animal);

#endif
