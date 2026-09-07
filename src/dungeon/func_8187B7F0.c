#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_8002694C;
extern s32 D_800814A0[3];

void func_8187B7F0(void *arg0, s16 *arg1)
{
    s16 *a = arg0;
    s16 temp;

    D_8002694C = 1;
    if (arg1[5] < func_800BCB04((s16)arg1[1], (u16)arg1[3], arg1[5] + 2)) {
        ((s32 *)arg1)[2] += *(s32 *)((u8 *)arg0 + 0xB4);
    }

    temp = (u16)a[8] - 4;
    a[8] = temp;
    if ((temp << 16) <= 0) {
        ((u16 *)a)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
