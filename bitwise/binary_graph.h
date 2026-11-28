#ifndef BINARY_GRAPH_H
#define BINARY_GRAPH_H

#include <stddef.h>

struct graph
{
    /* The adjacency matrix using each bit to determine adjacency where a link
     * beetween a and b means that the b-th bit (starting from the right) of
     * matrix[a] is set */
    size_t *matrix;
    size_t size; // The size of the graph cannot be more than the number of bits in a <code>size_t</code>
};

struct graph *graph_create(size_t size);
void graph_destroy(struct graph *graph);
void graph_add_arc(struct graph *graph, size_t a, size_t b);
int graph_has_self_loop(struct graph *graph, size_t i);
void graph_invert(struct graph *graph, size_t i);

#endif /* ! BINARY_GRAPH_H */
