#ifndef AIRSHIP_H
#define AIRSHIP_H

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>

struct engine
{
    int required_fuel;
    int started;
};

struct crew
{
    char **members;
    size_t crew_count;
    size_t crew_capacity;
};

struct airship
{
    // crew
    struct crew *crew;

    // ressource
    int fuel;
    int ammunition;

    // health
    int health;
    int max_health;

    // Cannons
    size_t nb_cannons;
    sem_t cannon_slots;

    // synchronisation
    pthread_mutex_t mutex;
    pthread_cond_t engine_cond;

    // Engines
    struct engine *engines;
    size_t nb_engine;
};

struct airship *init_airship(size_t capacity, int fuel, int ammunition,
                             int health, size_t nb_cannons);
void destroy_airship(struct airship *ship);

#endif /* AIRSHIP_H */
