#include "common.h"

/* Adjusts a0 by (unsigned)(a0/10) * a1->field_2, optionally x5 if a1->field_3 bit 0x40 is set, clamped to >=1. */
typedef struct S_8004A4E4 {
    u8 pad0;
    u8 pad1;
    s8 field_2;
    u8 field_3;
} S_8004A4E4;

s32 func_8004A4E4(s32 a0, S_8004A4E4 *a1) {
    s32 result = a0 + ((u32)a0 / 10) * a1->field_2;

    if (a1->field_3 & 0x40) {
        result = result * 5;
    }

    if (result <= 0) {
        result = 1;
    }

    return result;
}
