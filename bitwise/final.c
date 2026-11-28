#include "final.h"

typedef long long int ll;

size_t grid_count(const struct grid *grid)
{
	size_t cnt = 0;
	size_t line = grid->width*grid->height;
	for (size_t id = 0; id < line; id++) cnt += ((grid->data[id/8] >> (id%8)) & 0x1u);
	return cnt;
}

void grid_invert(struct grid *grid)
{
	size_t line = grid->width*grid->height;
	for(size_t id = 0; id < line; id++) grid->data[id/8] ^= (uint8_t)(0x1u << (id%8));
	
}

unsigned int grid_count_neighbors(const struct grid *grid, size_t x, size_t y)
{
	unsigned int cnt=0;
	for(int dy=-1; dy<=1; dy++){
		for(int dx=-1; dx<=1; dx++){
			ll nx=(ll)x+dx; ll ny=(ll)y+dy;
			if((dx || dy) && nx >= 0 && ny >= 0 && (size_t)nx < grid->width && (size_t)ny < grid->height){
				size_t id = ny * grid->width + nx;
				if((grid->data[id/8] >> (id%8)) & 0x1u) cnt++;
			}
		}
	}
	return cnt;
}
