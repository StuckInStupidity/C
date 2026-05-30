#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

struct node {
	int data;
	struct node *next;
	struct node *prev;
};

struct dlist {
	size_t size;
	struct node *head;
	struct node *tail;
};

struct dlist *dlist_init(void);
void dlist_clear(struct dlist *list);
size_t dlist_length(struct dlist *l);
void dlist_push_front(struct dlist *l, int data);
void dlist_push_back(struct dlist *l, int data);
void dlist_remove(struct dlist *list, int data);
struct dlist *dlist_from_str(char *str);
struct node *dlist_find(struct dlist *list, int data);
void dlist_concat(struct dlist *l1, struct dlist *l2);
void dlist_insert(struct dlist *l, int data, int i);
void split(struct node *l, struct node **list_l, struct node **list_r);
struct dlist *merge(struct node *left, struct node *right);
void dlist_merge_sort(struct dlist *l);

#endif