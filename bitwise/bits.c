#include "bits.h"

uint8_t set_bit(uint8_t value, unsigned int pos)
{
	return value | (0x1u << pos);
}

uint8_t unset_bit(uint8_t value, unsigned int pos)
{
	return value & ~(0x1u << pos);
}

uint8_t invert_bit(uint8_t value, unsigned int pos)
{
	return value ^ (0x1u << pos);
}

uint8_t extract_bits(uint8_t value, unsigned int start, unsigned int count)
{
	return (value >>= start) & ((0x1u << count) - 1);
}
