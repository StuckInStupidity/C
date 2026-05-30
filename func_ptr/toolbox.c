#include "toolbox.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array *sort(struct array *arr, comparator f)
{
	if(arr && f && arr->len >= 2){
	int swapped = 1; while(swapped){
		swapped = 0;
		for(size_t i = 0; i < arr->len - 1; i++){
			void *src = (char *)arr->data+i*arr->elem_size;
			void *dst = (char *)arr->data+(i+1)*arr->elem_size;
			if(f(src, dst) > 0){
				swapped = 1;
				char buf[arr->elem_size]; //memcpy(dst, src, size)
				memcpy(buf, src, arr->elem_size);
				memcpy(src, dst, arr->elem_size);
				memcpy(dst, buf, arr->elem_size);
			}
		}
	}}
	return arr;
}

struct array *map(struct array *arr, size_t output_size, mapper f)
{
	if(arr && f){
		void *itt = calloc(arr->len, output_size);
		for(size_t i=0;i<arr->len;i++){
			void *dst = (char *)itt+i*output_size;
			void *src = (char *)arr->data+i*arr->elem_size;
			f(dst, src);
		}
		arr->elem_size = output_size; free(arr->data); arr->data = itt;
	}
	return arr;
}

struct array *filter(struct array *arr, predicate f)
{
	if(arr && f){
		int c=0;
		for(size_t i=0;i<arr->len;i++) {void *it = (char *)arr->data+i*arr->elem_size; if(f(it)!=0) c++;}
		if(c==0) {arr->len=0;return arr;}
		char buf[c*arr->elem_size]; int j=0;
		for(size_t i=0;i<arr->len;i++) {
			void *it = (char *)arr->data+i*arr->elem_size; 
			if(f(it)!=0) {memcpy(buf+j*arr->elem_size, it, arr->elem_size); j++;}
		}
		arr->data = realloc(arr->data, c*arr->elem_size); memcpy(arr->data, buf, c*arr->elem_size); arr->len = c;
	}
	return arr;
}

void *reduce(struct array *arr, void *start_value, reducer f)
{
	if(arr && f){
	for(size_t i=0; i<arr->len;i++){
		void *r = (char *)arr->data+i*arr->elem_size;
		f(start_value, r);
	}}
	return start_value;
}

void foreach(struct array *arr, acceptor f)
{
	if(arr && f) for(size_t i = 0; i < arr->len; i++) {void *it = (char *)arr->data+i*arr->elem_size;f(it);}
}
