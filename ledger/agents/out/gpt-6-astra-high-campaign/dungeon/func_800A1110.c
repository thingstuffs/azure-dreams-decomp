#include "common.h"

s32 func_800A6D30();                             /* extern */

/* Combine the adjusted input divided by four with the helper result low bits. */
s32 func_800A6870(s16 input_value) {
    s16 adjusted_value;

    adjusted_value = input_value;
    if (input_value == 0xFF) {
        adjusted_value = 0x1E;
    }
    return ((s32) (adjusted_value << 0x10) >> 0x12) + (func_800A6D30(input_value) & 3);
}
