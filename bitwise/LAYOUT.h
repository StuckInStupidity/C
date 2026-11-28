#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>

/*
Memory alignment determines where data can be placed in memory.
For example, a uint32_t typically requires an address aligned to a multiple of 4 bytes, 
while a uint64_t typically requires an address aligned to a multiple of 8 bytes.
The compiler may therefore add padding between fields or at the end of a structure.
You can use sizeof to determine the size of a structure and offsetof (defined in <stddef.h>) to determine the offset of one of its fields.
*/

struct record
{
    char status;          // 1 byte, offset 0, add 7 bytes padding
    uint64_t timestamp;   // 8 bytes, offset 8, add no padding
    uint8_t priority;     // 1 byte, offset 16, add 3 bytes padding
    uint32_t id;	  // 4 bytes, offset 20, add no padding
    uint16_t value;	  // 2 bytes, offset 24, add 6 bytes padding
    char *category;	  // 8 bytes, offset 32, add no padding
};			  // total = 40 bytes
*/

struct record
{
    uint64_t timestamp;  // 8 bytes, offset 0, add no padding
    char *category;      // 8 bytes, offset 8, add no padding
    uint32_t id;	 // 4 bytes, offset 16, add no padding
    uint16_t value;	 // 2 bytes, offset 20, add no padding
    uint8_t priority;	 // 1 byte, offset 22, add no padding
    char status;	 // 1 byte, offset 23, add no padding
};			 // total = 24 bytes (since 24 is a multiple of 8)

#endif /* ! LAYOUT_H */
