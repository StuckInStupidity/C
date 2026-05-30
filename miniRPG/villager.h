#ifndef VILLAGER_H
#define VILLAGER_H

#include "weapons.h"

struct demon;

struct villager{
	char name[50];
	int cur_HP;
	int HP_max;
	struct gun *gun;
	int gun_mastery;
	int medicines;
	enum distance distance;
};

struct villager *init_villager(char name[50], int HP_max, struct gun *gun, int gun_mastery);
void pp_villager(struct villager *villager);
void destroy_villager(struct villager *villager);
void update_villager_hp(struct villager *villager, int amount);
void shoot(struct villager *villager, struct demon *demon);
void heal(struct villager *villager);
enum distance walk(struct villager *villager, int direction);
int prepare_medicine(struct villager *villager);

#endif