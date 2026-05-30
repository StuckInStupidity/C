#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct animal;

struct vector
{
    struct animal **animal;
    size_t size;
    size_t capacity;
};

struct vector *vector_init(size_t n);
struct vector *vector_resize(struct vector *v, size_t new_capacity);
struct vector *vector_append(struct vector *v, struct animal *animal);
void vector_destroy(struct vector *v);

#endif
