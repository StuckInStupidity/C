#ifndef LISTS_H
#define LISTS_H

#include <stddef.h>

struct list {
    struct list *next;
    int data;
};

struct dlist {
    struct dlist *next;
    struct dlist *prev;
    int data;
};

struct list *list_append(struct list *l, int e);
size_t list_count(struct list *l);
int list_insert(struct list **l, size_t index, int e);
struct list *list_get(struct list *l, size_t index);
struct list *list_find(struct list *l, int e);
struct list *list_delete_at(struct list **l, size_t index);
int list_remove(struct list **l, int e);
void list_destroy(struct list *l);
void list_print(struct list *l);
struct dlist *dlist_append(struct dlist *l, int e);
int dlist_insert(struct dlist **l, size_t index, int e);
struct dlist *dlist_delete_at(struct dlist **l, size_t index);
int dlist_remove(struct dlist **l, int e);
void dlist_print(struct dlist *l);
int is_palindrome(struct dlist *l);
struct list *reverse(struct list *l);
struct dlist *insertion_sort(struct dlist *l);
void split(struct list *l, struct list **list_l, struct list **list_r);
struct list *merge(struct list *left, struct list *right);
struct list *merge_sort(struct list *l);

#endif /* !LISTS_H */
