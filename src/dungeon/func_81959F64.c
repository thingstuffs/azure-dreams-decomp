#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern u16 D_800281F8[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

void func_81959F64(void *arg0, s16 *arg1)
{
    s16 *a = arg0;
    s16 temp;
    u16 count = D_800281F8[0];
    u16 z = arg1[5];
    u16 x = arg1[1];
    u16 y = arg1[3];

    D_800281F8[0] = count + 1;
    if (arg1[5] < func_800BCB04(x, y, z + 2)) {
        ((s32 *)arg1)[0] -= (D_8006CCD8[a[27]] * a[24]) << 11;
        ((s32 *)arg1)[1] -= (D_8006CCE8[a[27]] * a[24]) << 11;
        ((s32 *)arg1)[2] += (0xC0 - a[24]) << 10;
    }

    temp = (u16)a[24] - 8;
    a[24] = temp;
    if ((temp << 16) <= 0) {
        ((u16 *)a)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
