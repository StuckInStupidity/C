#ifndef PACKING_H
#define PACKING_H

#include <stdint.h>

struct record{
    char id[2]; // 2-character identifier
    uint8_t type; // Type of the record (4 bits)
    uint8_t priority; // Priority of the record (2 bits)
    uint16_t value; // Numerical value associated with the record (10 bits)
};

uint32_t pack_record(const struct record *record);
struct record *unpack_record(uint32_t packed);

enum firefly_type{
    FT_NO_LIGHT = 0,
    FT_BARELY = 1,
    FT_DIM = 2,
    FT_LOW = 3,
    FT_HIGH = 4,
    FT_BRIGHT = 5,
    FT_SUN = 6,
    FT_SUPERNOVA = 7,
    FT_UNIMAGINABLE = 8,
    FT_IDK_ANYMORE_TOO_BRIGHT = 9
};

struct firefly{
    char *name;
    enum firefly_type light_type;
    unsigned char leg_count;
};

void pack_firefly(const struct firefly *firefly, uint8_t *packed);
void unpack_firefly(const uint8_t *packed, struct firefly *firefly);

#endif /* ! PACKING_H */
