#include <stdlib.h>
#include <stdint.h>
#include "binary_graph.h"

struct graph *graph_create(size_t size){
	size_t b = 0;
	for (size_t i = ~(size_t)0; i; i >>= 1) b++;
	if (size==0 || size>b) return NULL;
	struct graph *g = malloc(sizeof(struct graph));
	g->matrix = calloc(size, sizeof(size_t));
	g->size = size;
	return g;
}

void graph_destroy(struct graph *graph){
	if(!graph) return;
	free(graph->matrix);
	free(graph);
}

void graph_add_arc(struct graph *graph, size_t a, size_t b){
	if(!graph || a>=graph->size || b>=graph->size) return;
	graph->matrix[a] |= ((size_t)1 << b);
}

int graph_has_self_loop(struct graph *graph, size_t i){
	if(!graph || i>=graph->size) return 0;
	if((graph->matrix[i] & (size_t)1 << i) >> i) return 1; //the >> i is not necessary
	else return 0;
}

void graph_invert(struct graph *graph, size_t i){
	if(!graph || i>=graph->size) return;
	else graph->matrix[i] ^= ~(SIZE_MAX << graph->size);
}