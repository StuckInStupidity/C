#include "compression.h"
#include <stdlib.h>

uint8_t *rle_compress(const uint8_t *data, size_t bit_count, size_t *compressed_size)
{
	if(!bit_count){*compressed_size=0;return NULL;}
	uint8_t *c = malloc(bit_count); //cant be bigger than that => worst case : 101010...
	size_t i=0;
	size_t nb=0;
	while(i<bit_count){
		uint8_t cur = (data[i/8] >> (i%8)) & 0x1u;
		unsigned cnt = 1; i++;
		while(i < bit_count && cnt < 127 && ((data[i/8] >> (i%8)) & 0x1u) == cur) {cnt++; i++;}
		uint8_t v = (uint8_t)((cur << 7) | cnt);
		c[nb++] = v;
	}
	*compressed_size = nb;
	return c;
}

uint8_t *rle_decompress(const uint8_t *data, size_t size, size_t *bit_count)
{
	if(!size){*bit_count=0;return NULL;}
	unsigned long long cnt=0;
	for(size_t i=0; i<size;i++) cnt+=(data[i] & 0x7F);
	*bit_count = cnt;
	uint8_t *c = calloc(cnt/8 + (cnt%8?1:0), 1);
	size_t id=0;
	for(size_t i=0; i < size; i++){
		unsigned t = data[i] & 0x7F;
		unsigned b = data[i] >> 7;
		for(size_t s=0; s<t; s++) {
			if(b) c[id/8] |= (uint8_t)(1u << (id%8)); 
			id++;
		}
	}
	return c;
}
