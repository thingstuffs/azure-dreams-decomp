#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_80026664;
extern s32 D_800814A0[3];

__asm__(".set D_80026664, 0x80026664");

void func_81875A78(void *arg0, s16 *arg1)
{
    s16 *a = arg0;
    s16 temp;

    D_80026664 = 1;
    if (arg1[5] < func_800BCB04((u16)arg1[1], (u16)arg1[3], arg1[5] + 2)) {
        ((s32 *)arg1)[2] += *(s32 *)((u8 *)arg0 + 0x48);
    }

    temp = (u16)a[25] - 4;
    a[25] = temp;
    if ((temp << 16) <= 0) {
        ((u16 *)a)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
