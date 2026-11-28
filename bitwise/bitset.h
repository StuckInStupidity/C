#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>
#include <stdint.h>

struct bitset{
    size_t size; // Number of bits stored in the bitset
    uint8_t *data; // Pointer to the allocated buffer
};

struct bitset *bitset_create(size_t size);
void bitset_destroy(struct bitset *bs);

void bitset_set(struct bitset *bs, size_t index, int value);
int bitset_get(const struct bitset *bs, size_t index);

#endif /* ! BITSET_H */
