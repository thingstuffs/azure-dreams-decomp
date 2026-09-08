#include "common.h"

#include "common.h"

s32 rand();                                         /* extern */

/* Scale a random value by the low 16 bits of the limit. */
u32 func_800374F4(s32 limit) {
    return (u32) ((limit & 0xFFFF) * ((rand() * 2) & 0xFFFF)) >> 0x10;
}
