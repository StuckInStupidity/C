#include "packing.h"
#include <stddef.h>
#include <stdlib.h>

uint32_t pack_record(const struct record *record)
{
	uint32_t v = (uint32_t)record->value << 22;
	v |= (uint32_t)record->priority << 20;
	v |= (uint32_t)record->type << 16;
	v |= (uint32_t)(uint8_t)record->id[1] << 8;
	v |= (uint32_t)(uint8_t)record->id[0];
	return v;
	//uint32_t cast avoids overflow whilst uint8_t avoids sign extension that could corrupt the expected bits
}

struct record *unpack_record(uint32_t packed)
{
	struct record *r = malloc(sizeof(struct record));
	r->id[0] = (char)(packed & 0xFF); //redudant mask cuz char will truncate anyway
	r->id[1] = (char)((packed >> 8) & 0xFF); //redudant mask cuz char will truncate anyway
	r->type = (uint8_t)((packed >> 16) & 0xF); // F to keep only 4 bits
	r->priority = (uint8_t)((packed >> 20) & 0x3); // 3 is for 2 bits
	r->value = (uint16_t)((packed >> 22) & 0x3FF); // redundant mask cuz value is the most significant bits so nothing after shifts is there
	return r;
}

void pack_firefly(const struct firefly *firefly, uint8_t *packed)
{
	uint8_t cnt = 0;
	while(firefly->name[cnt]) {packed[cnt+1]=(uint8_t)firefly->name[cnt]; cnt++;}
	packed[0] = cnt;
	uint8_t v = firefly->leg_count & 0xF;
	packed[cnt+1] = (uint8_t)(v << 4 | firefly->light_type); //light types are within 4 bits already
	//++cnt here could have not worked if the length of the name was 255 with uint8 it would have wrapped to 0
	
}

void unpack_firefly(const uint8_t *packed, struct firefly *firefly)
{
	uint8_t cnt = packed[0];
	for(uint8_t i=0; i < cnt; i++) firefly->name[i] = (char)packed[i+1]; //uint8_t i is fine cuz cnt is guaranteed at most 255
	firefly->name[cnt]='\0';
	uint8_t f = packed[cnt+1];
	firefly->leg_count = (unsigned char)(f >> 4);
	firefly->light_type = (enum firefly_type)(f & 0xF);
}
