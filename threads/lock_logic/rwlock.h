#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>
#include <stddef.h>

struct rwlock
{
    size_t read_nb; // The number of threads readin
    pthread_mutex_t internal; // The mutex protecting the variable `read_nb`
    pthread_mutex_t write; // The mutex locking for write
};

struct rwlock *rwlock_init();

int rwlock_destroy(struct rwlock *rwlock);

int rwlock_request_read(struct rwlock *rwlock);

int rwlock_end_read(struct rwlock *rwlock);

int rwlock_request_write(struct rwlock *rwlock);

int rwlock_end_write(struct rwlock *rwlock);

#endif /* ! RWLOCK_H */
