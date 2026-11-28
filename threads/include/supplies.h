#ifndef SUPPLIES_H
#define SUPPLIES_H

#include "airship.h"

struct load_args
{
    struct airship *ship;
    int amount;
};

void *load_worker(void *arg);
int load_supplies(struct airship *ship, int n, int amount);

#endif
