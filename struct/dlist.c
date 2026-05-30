#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct dlist *dlist_init(void)
{
	struct dlist *l = malloc(sizeof(struct dlist));
	if(!l) return NULL;
	l->head=NULL; l->tail=NULL; l->size = 0; return l;
}

void dlist_clear(struct dlist *list)
{
	if(list){
		while(list->head){
			struct node *n = list->head->next;
			free(list->head);
			list->head = n;
		}
		free(list);
	}
}

size_t dlist_length(struct dlist *l)
{
	if(!l) return 0;
    	struct node *n = l->head; size_t c = 0;
	while(n) {c++; n = n->next;}
	return c;
}

void dlist_push_front(struct dlist *l, int data)
{
	if(l){
		struct node *a = malloc(sizeof(struct node));
		a->data = data; a->prev = NULL; a->next = l->head;
		if(l->head==NULL) l->tail = a;
		else l->head->prev = a;
		l->head = a;
		(l->size)++;
	}
}

void dlist_push_back(struct dlist *l, int data)
{
	if(l){
		struct node *a = malloc(sizeof(struct node));
		a->data = data; a->prev = l->tail; a->next = NULL;
		if(l->tail==NULL) l->head = a;
		else l->tail->next = a;
		l->tail = a;
		(l->size)++;
	}
}

void dlist_remove(struct dlist *list, int data)
{
	if(list){
		struct node *d = list->head;
		while(d) {
			if(d->data==data){
				if(d->prev==NULL) {list->head=d->next;} else d->prev->next = d->next;
				if(d->next==NULL) {list->tail = d->prev;} else d->next->prev = d->prev;
				free(d); (list->size)--; return;
			}
			d = d->next;
		}
	}
}

struct dlist *dlist_from_str(char *str)
{
	struct dlist *l = dlist_init();
	if(!str) return l;
	int k=0; while(str[k]!='\0'){
		if(str[k]=='+') {
			k++; int n=0;
			while(str[k]!='\0' && str[k]!='+' && str[k]!='-'){
				n = n*10 + str[k]-'0';
				k++;
			}
			dlist_push_back(l, n);
		}
		if(str[k]=='-') {
			k++; int n=0;
			while(str[k]!='\0' && str[k]!='+' && str[k]!='-'){
				n = n*10 + str[k]-'0';
				k++;
			}
			dlist_remove(l, n);
		}
	}
	return l;
}

struct node *dlist_find(struct dlist *list, int data)
{
	if(!list) return NULL;
	struct node *d = list->head;
	while(d) {
		if(d->data==data) return d;
		d = d->next;
	}
	return NULL;
}

void dlist_print(struct dlist *l)
{
    	if(!l) return;
	printf("NULL");
	struct node *d = l->head;
	while(d) {
		printf("<->[%d]", d->data);
		d = d->next;
	}
	printf("<->NULL");
	printf("\n%d", l->size);
}

void dlist_concat(struct dlist *l1, struct dlist *l2)
{
	if(l1 && l2){
		struct node *f = l2->head;
		while(f) {dlist_push_back(l1, f->data); f = f->next;}
		dlist_clear(l2);
	}
}

void dlist_insert(struct dlist *l, int data, int i)
{
	if(l && i >= 0 && i <= l->size){
		if(i==0) dlist_push_front(l, data);
		else if(i==l->size) dlist_push_back(l, data);
		else{
			struct node *d = l->head; struct node *new = malloc(sizeof(struct node)); new->data = data;
			while(i--) d = d->next;
			new->next = d;
			new->prev = d->prev;
			d->prev->next = new;
			d->prev = new;
			(l->size)++;
		}
	}
}

void split(struct node *l, struct node **list_l, struct node **list_r)
{
    *list_l = l; *list_r = l; if(l){
    struct node *tmp = l; int c=0, i=1; while(tmp){c++;tmp=tmp->next;} tmp = l;
    while(i<c/2) {tmp=tmp->next;++i;} *list_r = tmp->next; if(*list_r) (*list_r)->prev = NULL; tmp->next = NULL;}
}

struct dlist *merge(struct node *left, struct node *right)
{
	static struct dlist f; // malloc will cause leaks and local variable will return a dangling pointer otherwise while static keeps memory and dont allocate on the heap
	f.head = NULL; f.tail = NULL; f.size = 0;
	if (!left) {f.head = right; return &f;} if (!right) {f.head = left; return &f;}
	struct node *head = NULL; if(left->data < right->data) {head = left; left=left->next;} else {head = right; right=right->next;}
	head->prev = NULL; struct node *tmp = head;
	while(left && right){
		if(left->data < right->data) {tmp->next = left; left->prev = tmp; left=left->next;}
		else {tmp->next = right; right->prev = tmp; right=right->next;}
		tmp = tmp->next;
	}
	while(left) {tmp->next = left; left->prev = tmp; left=left->next; tmp=tmp->next;}
	while(right) {tmp->next = right; right->prev = tmp; right=right->next; tmp=tmp->next;}
	f.head = head;	return &f;
}

void dlist_merge_sort(struct dlist *l)
{
	if(l && l->head && l->head->next){
		struct node *left = NULL; struct node *right = NULL;
		split(l->head, &left, &right);
		struct dlist left_l, right_l; 
		left_l.head = left; left_l.tail = NULL; left_l.size = 0;
		right_l.head = right; right_l.tail = NULL; right_l.size = 0;
		dlist_merge_sort(&left_l); dlist_merge_sort(&right_l);
		left = left_l.head; right = right_l.head;
		l->head = merge(left, right)->head;
		struct node *temp = l->head; while(temp->next) temp = temp->next; l->tail = temp;
	}
}
