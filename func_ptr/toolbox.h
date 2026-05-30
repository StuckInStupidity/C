#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <stddef.h>

typedef int (*comparator)(void *, void *);
typedef void (*mapper)(void *, void *);
typedef int (*predicate)(void *);
typedef void *(*reducer)(void *, void *);
typedef void (*acceptor)(void *);

struct array
{
    void *data;
    size_t len;
    size_t elem_size;
};

struct array *sort(struct array *arr, comparator f);
struct array *map(struct array *arr, size_t output_size, mapper f);
struct array *filter(struct array *arr, predicate f);
void *reduce(struct array *arr, void *start_value, reducer f);
void foreach(struct array *arr, acceptor f);

#endif /* ! TOOLBOX_H */
