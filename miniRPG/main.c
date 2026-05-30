#include <stdio.h>

#include "demon.h"
#include "villager.h"
#include "weapons.h"

int main()
{
// Init Villager
char name[50] = "Isabelle";
char gun_name[50] = "BFG";
struct gun *gun = init_gun(gun_name, 50, FAR, 16);
struct villager *villager =
    init_villager(name, 50, gun, 1);

// Init demon
char demon_name[50] = "Cyberdemon";
struct demon *demon = init_demon(NIGHTMARE, demon_name, 40, 5, CLOSE);

// Chase
pp_villager(villager);
chase(demon, villager);
pp_villager(villager);
destroy_villager(villager);
destroy_demon(demon);
// Init Villager
char name[50] = "Isabelle";
char gun_name[50] = "BFG";
struct gun *gun = init_gun(gun_name, 50, FAR, 16);

struct villager *villager =
    init_villager(name, 50, gun, 1);

// Init demon
char demon_name[50] = "Cyberdemon";
struct demon *demon = init_demon(NIGHTMARE, demon_name, 40, 5, FAR);

// Basic attack
basic_attack(demon, villager);
pp_villager(villager);
destroy_villager(villager);
destroy_demon(demon);
// Init Villager
char name[50] = "Isabelle";
char gun_name[50] = "BFG";

struct gun *gun = init_gun(gun_name, 50, FAR, 16);

struct villager *villager =
    init_villager(name, 50, gun, 1);

// Init demon
char demon_name[50] = "Cyberdemon";
struct demon *demon = init_demon(NIGHTMARE, demon_name, 40, 5, FAR);

// Draining attack
demon->cur_HP -= 10;
draining_attack(demon, villager);
pp_villager(villager);
pp_demon(demon);
destroy_demon(demon);
destroy_villager(villager);
// Init Villager
char name[50] = "Isabelle";
char gun_name[50] = "BFG";

struct gun *gun = init_gun(gun_name, 50, FAR, 16);

struct villager *villager =
    init_villager(name, 50, gun, 1);

// Init demon
char demon_name[50] = "Cyberdemon";
struct demon *demon = init_demon(NIGHTMARE, demon_name, 40, 5, FAR);

// Heavy attack
heavy_attack(demon, villager);
pp_villager(villager);
pp_demon(demon);
destroy_demon(demon);
destroy_villager(villager);
// Init Villager
char name[50] = "Isabelle";
char gun_name[50] = "BFG";
struct gun *gun = init_gun(gun_name, 50, FAR, 16);
struct villager *villager =
    init_villager(name, 500, gun, 1);

// Init demon
char demon_name[50] = "Cyberdemon";
struct demon *demon = init_demon(NIGHTMARE, demon_name, 40, 5, CLOSE);

// Demon action
demon_action(demon, villager); // Distance = Near but its range is close
demon_action(demon, villager); // In range and high HP
demon->cur_HP = demon->HP_max / 2;
demon_action(demon, villager); // In range and mid HP
demon->cur_HP = 1;
demon_action(demon, villager); // In range and low HP

destroy_villager(villager);
destroy_demon(demon);

}
