#include "common.h"

extern s32 func_800A6D30(void);

/* Shuffle a byte array in place using func_800A6D30() for random swap indices. */
void func_8004A9B0(u8 *bytes, s32 length) {
    s32 index;
    s32 swap_index;
    u8 saved_byte;
    for (index = length - 1; index > 0; index--) {
        swap_index = (func_800A6D30() & 0xFFFF) / ((0x7FFF / (index + 1)) + 1);
        saved_byte = bytes[index];
        bytes[index] = bytes[swap_index];
        bytes[swap_index] = saved_byte;
    }
}
