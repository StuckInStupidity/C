#ifndef WEAPONS_H
#define WEAPONS_H

enum distance
{
    CLOSE, //0
    NEAR, //1
    FAR, //2
};

struct gun
{
    char name[50];
    int damage;
    enum distance range;
    int magazine_size;
    int current_magazine;
};

struct gun *init_gun(char name[50], int damage, enum distance range, int magazine_size);
void reload(struct gun *gun);
void destroy_gun(struct gun *gun);

#endif