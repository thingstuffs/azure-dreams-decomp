#include "common.h"

extern s16 D_80025924[];
extern u32 D_800814A0[];

extern s16 func_800BCB04(s32 arg0, s32 arg1, s16 arg2);
extern s32 rand(void);

void func_818CEA8C(void *arg0, void *arg1)
{
    u8 *object = arg0;
    u8 *source = arg1;
    u16 x;
    u16 y;
    u16 z;
    u16 shifted_z;
    s32 limit;
    s32 value;

    z = *(u16 *)(source + 0xA);
    x = *(u16 *)(source + 2);
    y = *(u16 *)(source + 6);
    shifted_z = z + 2;
    D_80025924[0] = 1;
    limit = func_800BCB04(x, y, (s16)shifted_z);
    if (*(s16 *)(source + 0xA) < limit) {
        value = rand();
        *(u32 *)(source + 8) += 0x20000 + (value & 0xFFF);
    }

    *(s16 *)(object + 0x32) -= 8;
    if (*(s16 *)(object + 0x32) <= 0) {
        *(u16 *)(object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
