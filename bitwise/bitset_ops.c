#include "bitset_ops.h"
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

struct bitset *bitset_union(const struct bitset *a, const struct bitset *b)
{
	struct bitset *ans = bitset_create(a->size); if(!ans) return NULL;
	size_t cnt = a->size/8 + (a->size%8?1:0);
	for(size_t i = 0; i < cnt; i++) ans->data[i] = a->data[i]|b->data[i];
	if(a->size % 8) ans->data[cnt-1] &= (uint8_t)((1u<<(a->size%8))-1);
	return ans;
}

struct bitset *bitset_intersection(const struct bitset *a, const struct bitset *b)
{
	struct bitset *ans = bitset_create(a->size); if(!ans) return NULL;
	size_t cnt = a->size/8 + (a->size%8?1:0);
	for(size_t i = 0; i < cnt; i++) ans->data[i] = a->data[i]&b->data[i];
	if(a->size % 8) ans->data[cnt-1] &= (uint8_t)((1u<<(a->size%8))-1);
	return ans;
}

struct bitset *bitset_difference(const struct bitset *a, const struct bitset *b)
{
	struct bitset *ans = bitset_create(a->size); if(!ans) return NULL;
	size_t cnt = a->size/8 + (a->size%8?1:0);
	for(size_t i = 0; i < cnt; i++) ans->data[i] = a->data[i] & ~(b->data[i]);
	if(a->size % 8) ans->data[cnt-1] &= (uint8_t)((1u<<(a->size%8))-1);
	return ans;
}

struct bitset *bitset_symmetric_difference(const struct bitset *a, const struct bitset *b)
{
	struct bitset *ans = bitset_create(a->size); if(!ans) return NULL;
	size_t cnt = a->size/8 + (a->size%8?1:0);
	for(size_t i = 0; i < cnt; i++) ans->data[i] = a->data[i]^b->data[i];
	if(a->size % 8) ans->data[cnt-1] &= (uint8_t)((1u<<(a->size%8))-1);
	return ans;
}

int bitset_is_subset(const struct bitset *a, const struct bitset *b)
{
	//if we assume that a subset of b is valid if it does not contain any 1 that b cannot
	size_t cnt = a->size/8 + (a->size%8?1:0);
	size_t cnt2 = b->size/8 + (b->size%8?1:0);
	size_t r = cnt > cnt2 ? cnt2 : cnt;
	for(size_t i = 0; i < r; i++) if((a->data[i] & b->data[i]) != a->data[i]) return 0;
	for(size_t i = r; i < cnt; i++) if(a->data[i]) return 0;
	return 1;
}
