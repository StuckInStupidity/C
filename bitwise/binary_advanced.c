#include <stdlib.h>
#include <stdint.h>
#include "binary_advanced.h"

size_t graph_get_to(struct graph* graph, size_t node){
	if(!graph || node >= graph->size) return 0;
	size_t ok = (size_t)1 << node;
	size_t i=0, id=0;
	while(id < graph->size){
		size_t v = ok;
		if(ok & ((size_t)1 << i)) ok |= graph->matrix[i];
        	id = (ok==v)? id+1 : 0;
        	i = (i+1)%graph->size;	
	}
	return ok;
}

int graph_is_strongly_connected(struct graph *graph){
	if(!graph) return 2;
	size_t c = ~(SIZE_MAX << graph->size);
	for (size_t i=0; i<graph->size; i++) if(graph_get_to(graph, i) != c) return 0;
	return 1;
}

size_t graph_get_scc_with(struct graph *graph, size_t node){
	if(!graph || node >= graph->size) return 0;
	size_t s = graph_get_to(graph, node);
	size_t ans = 0;
	for (size_t j = 0; j < graph->size; j++) {
		size_t ret = graph_get_to(graph, j);
		if ((s & ((size_t)1 << j)) && (ret & ((size_t)1 << node))) ans |= (size_t)1 << j;
	}
	return ans;
}