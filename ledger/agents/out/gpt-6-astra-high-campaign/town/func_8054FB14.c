#include "common.h"

extern void *D_80016000;

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

/* Adds 100 to the stored value, divides by 100, and caps the result at ten. */
s32 func_8054FB14(void) {
    u32 value;

    value = (FIELD(FIELD(D_80016000, void **, 0x38), u32 *, 0x2D5C) + 0x64U) / 100U;
    if ((s32)value >= 0xB) {
        value = 0xAU;
    }
    return value;
}
