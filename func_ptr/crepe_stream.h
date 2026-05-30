#ifndef CREPE_STREAM_H
#define CREPE_STREAM_H

#include "toolbox.h"

enum dough
{
    WHEAT,
    BUCKWHEAT,
};

enum topping
{
    NOTHING,

    // Sweet
    SUGAR,
    CHOCOLATE,
    WHIPPED_CREAM,

    // Savory
    CHEESE,
    MEAT,
    EGG,
};

struct crepe
{
    char *name;
    enum dough dough;
    enum topping inside;
    enum topping outside;
    int price;
};

int predica(const void *n, const void *nn);
struct array *sort_by_prices(struct array *arr);
struct array *names(struct array *arr);
struct array *vegetarian(struct array *arr);
int total_price(struct array *arr);
void print_menu(struct array *arr);

#endif /* ! CREPE_STREAM_H */
