#ifndef CANNON_H
#define CANNON_H

#include "airship.h"

struct cannon_args
{
    struct airship *ship;
    struct airship *enemy;
    int result;
};

int cannon_hit(void);

int shoot(struct airship *ship, struct airship *enemy);

void *fire_cannon(void *arg);

int fire_cannons(struct airship *ship, struct airship *enemy, size_t nb_shots);

#endif /* CANNON_H */
