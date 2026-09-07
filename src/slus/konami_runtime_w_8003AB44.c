#include "common.h"

#include "common.h"

extern s32 D_8006A8C8[5];
extern s32 D_8006A8DC[5];
extern s32 func_8004D880(s32 arg0);
extern void func_8004D91C(s32 arg0, s16 *arg1);
extern void MoveImage(void *rect, s32 x, s32 y);

void func_8003AB44(u8 *arg0, s16 arg1, s16 arg2, s32 arg3, s16 arg4, s32 arg5)
{
    s16 rect[4];
    s32 temp_a3;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s2;
    volatile u8 *x_table;
    volatile u8 *y_table;

    temp_a1 = arg1;
    temp_a3 = arg3 & 0xFF;
    x_table = (volatile u8 *)D_8006A8C8;
    temp_s2 = temp_a3 * 4;
    temp_s0 = arg4 + temp_a1 * *(volatile s32 *)(x_table + temp_s2);
    if ((u32)(temp_s0 - 0x140) < 0x2C0) {
        func_8004D91C(func_8004D880(arg0[1] | (arg0[0] << 8)) & 0xFF, rect);
        temp_a2 = arg2;
        y_table = (volatile u8 *)D_8006A8DC;
        MoveImage(rect, temp_s0, (s16)arg5 + temp_a2 * *(volatile s32 *)(y_table + temp_s2));
    }
}
