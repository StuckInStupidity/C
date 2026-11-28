#ifndef BITSET_OPS_H
#define BITSET_OPS_H

#include <stddef.h>
#include <stdint.h>

struct bitset{
    size_t size;
    uint8_t *data;
};

struct bitset *bitset_union(const struct bitset *a, const struct bitset *b);
struct bitset *bitset_intersection(const struct bitset *a, const struct bitset *b);
struct bitset *bitset_difference(const struct bitset *a, const struct bitset *b);
struct bitset *bitset_symmetric_difference(const struct bitset *a, const struct bitset *b);
int bitset_is_subset(const struct bitset *a, const struct bitset *b);

#endif /* ! BITSET_OPS_H */
