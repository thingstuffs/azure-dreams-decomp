#include "common.h"

extern s16 D_80025924[];
extern u32 D_800814A0[];

extern s16 func_800BCB04(s32 arg0, s32 arg1, s16 arg2);
extern s32 rand(void);

/* Raises the source toward its height limit and flags the object when its counter expires. */
void func_818CEA8C(void *object_data, void *source_data)
{
    u8 *object = object_data;
    u8 *source = source_data;
    u16 x;
    u16 y;
    u16 z;
    u16 probe_z;
    s32 height_limit;
    s32 random_value;

    z = *(u16 *)(source + 0xA);
    x = *(u16 *)(source + 2);
    y = *(u16 *)(source + 6);
    probe_z = z + 2;
    D_80025924[0] = 1;
    height_limit = func_800BCB04(x, y, (s16)probe_z);
    if (*(s16 *)(source + 0xA) < height_limit) {
        random_value = rand();
        *(u32 *)(source + 8) += 0x20000 + (random_value & 0xFFF);
    }

    *(s16 *)(object + 0x32) -= 8;
    if (*(s16 *)(object + 0x32) <= 0) {
        *(u16 *)(object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
