#ifndef ENGINE_H
#define ENGINE_H

#include "airship.h"

struct engine_args
{
    struct airship *ship;
    struct engine *engine;
    size_t *working;
};

int init_engines(struct airship *ship, const int *requirements, size_t n);

void *start_engine(void *arg);
int start_engines(struct airship *ship);

void destroy_engines(struct airship *ship);

#endif /* ENGINE_H */
