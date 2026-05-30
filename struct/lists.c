#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct list *list_append(struct list *l, int e)
{
  struct list *ll = malloc(sizeof(struct list));
  ll->data = e;
  ll->next = l;
  return ll;
}

size_t list_count(struct list *l)
{
    struct list *tmp = l; size_t c=0;
    while(tmp) {c++; tmp = tmp->next;}
    return c;
}

int list_insert(struct list **l, size_t index, int e)
{
	struct list *a = malloc(sizeof(struct list));
	if(!a) return 1;
	a->data = e;
	if(index==0){
	a->next = *l;
	*l = a;}
	else{
		struct list *tmp = *l;
		while(tmp && index>1) {tmp = tmp->next; index--;}
		if(tmp){
		a->next = tmp->next;
		tmp->next = a;
		}
		else {free(a); return 1;}
	}
	return 0;
}

struct list *list_get(struct list *l, size_t index)
{
	struct list *tmp = l;
	while(tmp && index) {tmp = tmp->next; index--;}
	if(!index && tmp) return tmp;
	else return NULL;
}

struct list *list_find(struct list *l, int e)
{
	struct list *tmp = l;
	while(tmp){if(tmp->data == e) return tmp; tmp=tmp->next;}
	return NULL;
}

struct list *list_delete_at(struct list **l, size_t index)
{
	if(*l==NULL) return NULL;
	struct list *tmp = *l; struct list *t = tmp;
	if(index==0) {*l = (*l)->next; return tmp;}
	while(tmp && index>0) {t=tmp; tmp = tmp->next; index--;}
	if(tmp) {
		t->next = tmp->next;
		return tmp;
	}
	else return NULL;
}

int list_remove(struct list **l, int e)
{
	struct list *tmp = *l; struct list *t = NULL;
	while(tmp) {if(tmp->data == e) {if(!t) *l = tmp->next; else t->next = tmp->next; free(tmp); return 1;} t=tmp; tmp=tmp->next;}
	return 0;
}

void list_destroy(struct list *l)
{
    if(l) {list_destroy(l->next); free(l);}
    //while(l) {struct list *tmp = l->next; free(l); l=tmp;}
}

void list_print(struct list *l)
{
    if(!l) printf("empty_list\n");
    else{
	struct list *tmp = l;
	while(tmp) {if(tmp->next) printf("%d -> ", tmp->data); else printf("%d\n", tmp->data); tmp = tmp->next;}
    }
}

struct dlist *dlist_append(struct dlist *l, int e)
{
    struct dlist *c = malloc(sizeof(struct dlist));
    if(!c) return NULL;
    c->prev = NULL;
    c->data = e;
    c->next = l;
    if(l) l->prev = c;
    return c;
}

int dlist_insert(struct dlist **l, size_t index, int e)
{
	struct dlist *d = malloc(sizeof(struct dlist));
	if(!d) return 1;
	d->data = e;
	if(index==0){
	d->prev = NULL;
	d->next = *l;
	(*l)->prev = d;
	*l = d;}
	else{
		struct dlist *tmp = *l;
		while(tmp && index>1) {tmp = tmp->next; index--;}
		if(tmp){
		d->next = tmp->next;
		d->prev = tmp;
		if(tmp->next) tmp->next->prev = d;
		tmp->next = d;
		}
		else {free(d); return 1;}
	}
	return 0;
}

struct dlist *dlist_delete_at(struct dlist **l, size_t index)
{
	if(*l==NULL) return NULL;
	struct dlist *tmp = *l; struct dlist *t = tmp;
	if(index==0) {*l = (*l)->next; (*l)->prev = NULL; return tmp;}
	while(tmp && index>0) {t=tmp; tmp = tmp->next; index--;}
	if(tmp) {
		t->next = tmp->next;
		if(tmp->next) tmp->next->prev = t;
		return tmp;
	}
	else return NULL;
}

int dlist_remove(struct dlist **l, int e)
{
	struct dlist *tmp = *l; struct dlist *t = NULL;
	while(tmp) {if(tmp->data == e) {if(!t) {*l = tmp->next; (*l)->prev = NULL;} else {t->next = tmp->next; if(tmp->next) tmp->next->prev = t;} free(tmp); return 1;} t=tmp; tmp=tmp->next;}
	return 0;
}

void dlist_print(struct dlist *l)
{
    if(!l) printf("empty_dlist\n");
    else{
	struct dlist *tmp = l;
	while(tmp) {if(tmp->next) printf("%d <-> ", tmp->data); else printf("%d\n", tmp->data); tmp = tmp->next;}
    }
}

int is_palindrome(struct dlist *l)
{
    if(!l) return 1;
    struct dlist *tmp = l; struct dlist *pmt = l; while(pmt->next) pmt = pmt->next;
    while(pmt!=tmp) {if(pmt->data!=tmp->data) return 0; pmt = pmt->prev; tmp=tmp->next;}
    return 1;
}

struct list *reverse(struct list *l)
{
    if(!l) return NULL;
    struct list *prev = NULL; struct list *cur = l; struct list *n = l->next;
    while(cur) {cur->next = prev; prev = cur; cur = n; if(n) n = n->next;}
    return prev;
}

struct dlist *insertion_sort(struct dlist *l)
{
	struct dlist *tmp = l; struct dlist *head = l;
	while(tmp){
		struct dlist *t = tmp->next;
		while(t){
			if(t->data < tmp->data) {
				t->prev->next = t->next;
				if(t->next) t->next->prev = t->prev;
				t->prev = tmp->prev; 
				if(tmp->prev) tmp->prev->next = t; else head = t;
				t->next = tmp;
				tmp->prev = t;
				tmp = t;
			}
			t = t->next;
		}
		tmp = tmp->next;
	}
	return head;
}

void split(struct list *l, struct list **list_l, struct list **list_r)
{
    *list_l = l; *list_r = l; if(l){
    struct list *tmp = l; int c=0, i=1; while(tmp){c++;tmp=tmp->next;} tmp = l;
    while(i<c/2) {tmp=tmp->next;++i;} *list_r = tmp->next; tmp->next = NULL;}
}

struct list *merge(struct list *left, struct list *right)
{
	if (!left) return right; if (!right) return left;
	struct list *head = NULL; if(left->data < right->data) {head = left; left=left->next;} else {head = right; right=right->next;}
	struct list *tmp = head;
	while(left && right){
		if(left->data < right->data) {tmp->next = left; left=left->next;}
		else {tmp->next = right; right=right->next;}
		tmp = tmp->next;
	}
	while(left) {tmp->next = left; left=left->next; tmp=tmp->next;}
	while(right) {tmp->next = right; right=right->next; tmp=tmp->next;}
	return head;
}

struct list *merge_sort(struct list *l)
{
	if(!l || (l && !(l->next))) return l;
	struct list *left = NULL; struct list *right = NULL;
	split(l, &left, &right);
	left = merge_sort(left); right = merge_sort(right);
	return merge(left, right);
}


