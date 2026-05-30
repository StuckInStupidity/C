#include "villager.h"
#include "demon.h"
#include "weapons.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

struct villager *init_villager(char name[50], int HP_max, struct gun *gun, int gun_mastery){
	struct villager *villager = malloc(sizeof(struct villager)); if(!villager) return NULL;
	strcpy(villager->name, name);
	villager->medicines =10;
	villager->distance = NEAR;
	villager->HP_max = HP_max;
	villager->cur_HP = HP_max;
	villager->gun = gun;
	villager->gun_mastery = gun_mastery;
	return villager;
}

void update_villager_hp(struct villager *villager, int amount){
	if(villager) {
		villager->cur_HP -= amount;
		if(villager->cur_HP <=0) printf("You died.\n");
		else if(villager->cur_HP > villager->HP_max) villager->cur_HP = villager->HP_max;
	}
}

void destroy_villager(struct villager *villager){
	if(villager) {if(villager->gun) destroy_gun(villager->gun); free(villager);}
}

void shoot(struct villager *villager, struct demon *demon){
	if(villager && demon) {
		if(!villager->gun) {printf("Equip a gun before trying to use one.\n");return;}
		else if(villager->gun->current_magazine == 0) {printf("Empty gun : You gotta reload.\n"); return;}
		else {
			villager->gun->current_magazine--;
			if(villager->distance > villager->gun->range) printf("No demon in range.\n");
			else {int d = villager->gun->damage+villager->gun_mastery; if(d<0) d=0; demon->cur_HP -= d; printf("BAM! %s lost %d HP.\n", demon->name,d);}
		}
	}
}

void heal(struct villager *villager){
	if(villager){
		if(villager->medicines == 0) printf("No medicine left, maybe prepare some ?\n");
		else {villager->medicines--; int m = villager->HP_max*0.25;if(villager->cur_HP + m > villager->HP_max) m = villager->HP_max - villager->cur_HP;printf("Nice, you healed %d HP.\n", m);villager->cur_HP+=m;}
	}
}

enum distance walk(struct villager *villager, int direction){
	if(villager==NULL) return NEAR;
	if(direction>=0){
		if(villager->distance == CLOSE) printf("Too close.\n");
		else printf("You decided to move.\n");
		if(villager->distance == FAR) villager->distance = NEAR;
		else if(villager->distance == NEAR) villager->distance = CLOSE;
	}
	else{
		if(villager->distance == FAR) printf("I can't run away.\n");
		else printf("You decided to move.\n");
		if(villager->distance == CLOSE) villager->distance = NEAR;
		else if(villager->distance == NEAR) villager->distance = FAR;
	}
	return villager->distance;
}

int prepare_medicine(struct villager *villager){
	if(villager) {if(villager->medicines < 10) villager->medicines++; printf("Preparation ready !\n"); return villager->medicines;}
	else return 0;
}




