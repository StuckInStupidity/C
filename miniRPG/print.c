#include <stdio.h>

#include "demon.h"
#include "villager.h"
#include "weapons.h"

void pp_villager(struct villager* villager){
	if(villager){
		printf("============================= Villager info =============================\n");
		printf("Name: %s\n", villager->name);
		printf("HP: %d/%d\n", villager->cur_HP, villager->HP_max);
		printf("Gun: %s | Magazine: %d/%d | Mastery: %d\n", villager->gun->name, villager->gun->current_magazine, villager->gun->magazine_size, villager->gun_mastery);
		printf("Medicine: %d/10\n", villager->medicines);
		if(villager->distance == NEAR) printf("Distance: Near\n");
		else if(villager->distance == FAR) printf("Distance: Far\n");
		else if(villager->distance == CLOSE) printf("Distance: Close\n");
	}
}

void pp_demon(struct demon* demon){
	if(demon){
		printf("============================= Demon info =============================\n");
		printf("Name: %s | Category: ", demon->name);
		if(demon->category == PARASITE) printf("Parasite\n");
		else if(demon->category == THREAT) printf("Threat\n");
		else if(demon->category == NIGHTMARE) printf("Nightmare\n");
		else if(demon->category == CALAMITY) printf("Calamity\n");
		else if(demon->category == TOM_NOOK) printf("Tom Nook\n");		
		printf("Base damage: %d | Range: ", demon->damage);
		if(demon->range == NEAR) printf("Near\n");
		else if(demon->range == FAR) printf("Far\n");
		else if(demon->range == CLOSE) printf("Close\n");
		printf("HP: %d/%d\n", demon->cur_HP, demon->HP_max);
	}
}