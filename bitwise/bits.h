#ifndef BITS_H
#define BITS_H

#include <stdint.h>

uint8_t set_bit(uint8_t value, unsigned int pos);
uint8_t unset_bit(uint8_t value, unsigned int pos);
uint8_t invert_bit(uint8_t value, unsigned int pos);

uint8_t extract_bits(uint8_t value, unsigned int start, unsigned int count);

#endif /* ! BITS_H */
