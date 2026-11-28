#ifndef FINAL_H
#define FINAL_H

#include <stddef.h>
#include <stdint.h>

struct grid{
    size_t width;
    size_t height;
    uint8_t *data;
};

size_t grid_count(const struct grid *grid);
void grid_invert(struct grid *grid);
unsigned int grid_count_neighbors(const struct grid *grid, size_t x, size_t y);

#endif /* ! FINAL_H */
