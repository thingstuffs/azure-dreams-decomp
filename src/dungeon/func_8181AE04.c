#include "common.h"

extern s32 rand(void);
extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_80025914;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[];

void func_8181AE04(void *arg0, s16 *arg1)
{
    s16 *a = arg0;
    s16 temp;
    s32 x;
    s32 y;

    D_80025914 = 1;
    if (arg1[5] < func_800BCB04((u16)arg1[1], (u16)arg1[3], arg1[5] + 2)) {
        x = ((D_8006CCD8[a[10]] * a[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)arg1)[0] += x;

        y = ((D_8006CCE8[a[10]] * a[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)arg1)[1] += y;
        ((s32 *)arg1)[2] += 0x20000 + (rand() & 0xFFF);
    }

    temp = (u16)a[25] - 8;
    a[25] = temp;
    if ((temp << 16) <= 0) {
        ((u16 *)a)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
