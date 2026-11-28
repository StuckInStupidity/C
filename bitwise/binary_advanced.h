#ifndef BINARY_ADVANCED_H
#define BINARY_ADVANCED_H

#include <stddef.h>

#include "binary_graph.h"

size_t graph_get_to(struct graph *graph, size_t node);
int graph_is_strongly_connected(struct graph *graph);
size_t graph_get_scc_with(struct graph *graph, size_t node);

#endif // ! BINARY_ADVANCED_H
