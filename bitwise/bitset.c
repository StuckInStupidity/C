#include "bitset.h"
#include <stdlib.h>

struct bitset *bitset_create(size_t size)
{
	struct bitset *b = malloc(sizeof(struct bitset));
	b->size = size;
	b->data = NULL;
	if(size > 0){
		int r = size%8 ? 1 : 0;
		b->data = calloc(size/8 + r, sizeof(uint8_t));		
	}
	return b;
}

void bitset_destroy(struct bitset *bs)
{
	if(bs) {free(bs->data);free(bs);}
}

void bitset_set(struct bitset *bs, size_t index, int value)
{
	//bit i is stored at position i % 8 in byte i / 8
	if(bs && index < bs->size){
		uint8_t mask = (uint8_t)(0x1u << (index%8));
		if(value) bs->data[index/8] |= mask;
		else bs->data[index/8] &= (uint8_t)~mask; 
	}
}

int bitset_get(const struct bitset *bs, size_t index)
{
	if(!bs || index >= bs->size) return -1;
	return ((bs->data[index/8] >> (index%8)) & 0x1u);
}
