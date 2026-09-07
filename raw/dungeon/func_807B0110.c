#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

void func_807B0110(void *arg0, s16 *arg1) {
    s16 *a = arg0;
    s16 temp;

    if (arg1[5] < func_800BCB04((u16) arg1[1], (u16) arg1[3], arg1[5] + 2)) {
        ((s32 *) arg1)[0] -= (D_8006CCD8[a[10]] * a[25]) << 11;
        ((s32 *) arg1)[1] -= (D_8006CCE8[a[10]] * a[25]) << 11;
        ((s32 *) arg1)[2] += (0xC0 - a[25]) << 10;
    }

    temp = (u16) a[25] - 8;
    a[25] = temp;
    if ((temp << 16) <= 0) {
        ((u16 *) a)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
