#ifndef DEMON_H
#define DEMON_H

#include "weapons.h"

struct villager;

enum demon_category
{
    PARASITE = 1,
    THREAT,
    NIGHTMARE,
    CALAMITY,
    TOM_NOOK
};

struct demon{
	enum demon_category category;
	char name[50];
	int damage;
	enum distance range;
	int cur_HP;
	int HP_max;
};

struct demon *init_demon(enum demon_category category, char name[50], int HP_max, int damage, enum distance range);
void pp_demon(struct demon *demon);
void destroy_demon(struct demon *demon);
void basic_attack(struct demon *demon, struct villager *target);
void draining_attack(struct demon *demon, struct villager *target);
void heavy_attack(struct demon *demon, struct villager *target);
void chase(struct demon *demon, struct villager *villager);
void update_demon_hp(struct demon *demon, int amount);
void demon_action(struct demon *demon, struct villager *villager);

#endif