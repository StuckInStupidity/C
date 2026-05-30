#include "crepe_stream.h"
#include "toolbox.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int predica(const void *n, const void *nn)
{
    const struct crepe *c = n, *cc = nn;
    if(c->price%2==0){
	if(cc->price%2==0){
		return c->price - cc->price;
	}
	else return -1;
    }
    else {
	if(cc->price%2==0) return 1;
	else return cc->price - c->price;
    }
}

struct array *sort_by_prices(struct array *arr)
{
    sort(NULL, NULL);
    if(arr) qsort(arr->data,arr->len,arr->elem_size,predica);
    return arr;
}

struct array *names(struct array *arr)
{
	map(NULL, 0, NULL);
	if(arr){
	struct array *ar = malloc(sizeof(struct array)); ar->len = arr->len; ar->elem_size = sizeof(char *); ar->data = malloc(arr->len*sizeof(char *));
	for(size_t i=0; i<arr->len; i++){
		struct crepe *s = (struct crepe *)((char *)arr->data + i * arr->elem_size);
		((char **)ar->data)[i] = s->name;
	}
	return ar;
	} return arr;
}

struct array *vegetarian(struct array *arr)
{
	filter(NULL, NULL);
	if(arr){
		size_t i=0; while(i<arr->len){
			struct crepe *s = (struct crepe *)((char *)arr->data + i * arr->elem_size);
			if(s->inside == MEAT || s->outside == MEAT) {
				size_t j=i; 
				while(j<arr->len-1) {memcpy((char *)arr->data+j*arr->elem_size,(char *)arr->data+(j+1)*arr->elem_size,arr->elem_size);j++;}
				arr->len = arr->len - 1;
			} else i++;
		}
		arr->data = realloc(arr->data, arr->len*arr->elem_size);
	}
	return arr;
}

int total_price(struct array *arr)
{
	reduce(NULL, 0, NULL);
	int res=0;
	if(arr){
		for(size_t i=0; i<arr->len; i++){
			struct crepe *s = (struct crepe *)((char *)arr->data + i * arr->elem_size);
			res+=s->price;
		}
	}
	return res;
}

void print_menu(struct array *arr)
{
	foreach(NULL, NULL);
	if(arr){
	char *st[] = {"nothing","sugar","chocolate","whipped cream", "cheese", "meat", "egg"};
	for(size_t i=0; i<arr->len; i++){
		struct crepe *s = (struct crepe *)((char *)arr->data + i * arr->elem_size);
		char *ss = (s->dough == WHEAT) ? "wheat" : "buckwheat";
		printf("%s: $%d\n- Made out of %s\n", s->name, s->price, ss);
		printf("- Contains %s with %s on top\n", st[s->inside], st[s->outside]);
	}}
}
