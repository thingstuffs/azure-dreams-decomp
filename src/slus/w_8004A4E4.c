#include "common.h"

typedef struct S_8004A4E4 {
    u8 pad0;
    u8 pad1;
    s8 field_2;
    u8 field_3;
} S_8004A4E4;

/* Applies a signed correction and optional fivefold multiplier to the base value, with a minimum of one. */
s32 func_8004A4E4(s32 base_value, S_8004A4E4 *modifier) {
    s32 result = base_value + ((u32)base_value / 10) * modifier->field_2;

    if (modifier->field_3 & 0x40) {
        result = result * 5;
    }

    if (result <= 0) {
        result = 1;
    }

    return result;
}
