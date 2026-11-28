#ifndef UPDATE_CREW_H
#define UPDATE_CREW_H

#include "airship.h"
#include <stddef.h>

struct crew_args
{
    struct airship *ship;
    const char *name;
    int error;
};

struct crew_search_args
{
    const struct crew *crew;
    const char *name;
    int found;
};

void *find_pirate_worker(void *arg);

size_t crew_strlen(const char *str);
int crew_strcmp(const char *s1, const char *s2);
char *crew_strcpy(char *dest, const char *src);

void *add_pirate(void *arg);
void *remove_pirate(void *arg);

void add_locked(struct crew_args *a);
void remove_locked(struct crew_args *a);

int update_crew(struct airship *ship, const char **names, size_t n);

#endif
