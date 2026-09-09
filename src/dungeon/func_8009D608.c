#include "common.h"

extern s32 D_800E296C[];

/* Adds to the big-endian value at offset 0x41, saturates at 0xFFFF, and sets the update flag. */
void func_800A2D68(u8 *record, u16 amount)
{
    u32 value;

    value = (record[0x41] << 8) | record[0x42];
    value += amount;
    if (value > 0xFFFF) {
        value = 0xFFFF;
    }
    record[0x41] = value >> 8;
    record[0x42] = value;
    D_800E296C[0] |= 0x100000;
}
