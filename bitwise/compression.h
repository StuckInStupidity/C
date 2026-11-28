#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h>
#include <stdint.h>

uint8_t *rle_compress(const uint8_t *data, size_t bit_count, size_t *compressed_size);
uint8_t *rle_decompress(const uint8_t *data, size_t size, size_t *bit_count);

#endif /* ! COMPRESSION_H */
