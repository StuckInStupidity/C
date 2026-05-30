#include "demon.h"
#include "villager.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct demon *init_demon(enum demon_category category, char name[50], int HP_max, int damage, enum distance range){
	struct demon *demon = malloc(sizeof(struct demon)); if(!demon) return NULL;
	demon->category = category;
	strcpy(demon->name, name);
	demon->damage = damage*category;
	demon->range = range;
	demon->HP_max = HP_max*category;
	demon->cur_HP = demon->HP_max;	
	return demon;
}

void update_demon_hp(struct demon *demon, int amount){
	if(demon){
		demon->cur_HP -= amount;
		if(demon->cur_HP <= 0) printf("You killed the demon %s !!\n", demon->name);
		else if(demon->cur_HP > demon->HP_max) demon->cur_HP = demon->HP_max;
	}
}

void destroy_demon(struct demon *demon){
	if(demon) free(demon);
}

void chase(struct demon *demon, struct villager *villager){
	if(villager && demon){
		if(villager->distance == FAR) villager->distance = NEAR;
		else if(villager->distance == NEAR) villager->distance = CLOSE;
		printf("The demon %s is chasing you.\n", demon->name);
	}
}

void basic_attack(struct demon *demon, struct villager *target){
	if(target && demon){
		if(demon->range >= target->distance) {printf("RAAAAAGH! %s attacks you to deal %d damage.\n", demon->name, demon->damage); target->cur_HP-=demon->damage;}
	}
}

void draining_attack(struct demon *demon, struct villager *target){
	if(target && demon){
		int d = demon->damage >= 2 ? demon->damage >> 1 : 1; int h = d >> 1;
		if(demon->range >= target->distance) {printf("SLURRRRP! %s attacks you to deal %d damage and regenerates %d HP.\n", demon->name, d, h);target->cur_HP-=d;demon->cur_HP+=h;}
	}
}

void heavy_attack(struct demon *demon, struct villager *target){
	if(target && demon){
		if(demon->range >= target->distance) {printf("BAM! %s attacks you with all his strength to deal %d damage.\n", demon->name, demon->damage*2);target->cur_HP-=demon->damage*2;demon->cur_HP-=0.1*demon->HP_max;}
	}
}

void demon_action(struct demon *demon, struct villager *villager){
	if(villager && demon){
		if(villager->distance > demon->range) chase(demon, villager);
		else if(demon->cur_HP > 0.75*demon->HP_max) heavy_attack(demon, villager);
		else if(demon->cur_HP < 0.25*demon->HP_max) draining_attack(demon, villager);
		else basic_attack(demon, villager);
	}
}






















