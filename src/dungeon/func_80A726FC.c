#include "common.h"

extern void func_80047784(void *, s16, s16);
extern s16 D_80083228[5];
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern u8 D_80174158[9];

void func_80171EFC(void *arg0, s32 *arg1, void *arg2, void *arg3)
{
    s32 direction;
    s16 *direction_x;

    direction = (*(volatile u16 *)((s8 *)arg3 + 0x2A) >> 9) & 7;
    *((s8 *)arg0 + 0x9A) = 0x10;
    *((s8 *)arg0 + 0x9B) = 0;
    *(u8 **)((s8 *)arg2 + 0x2C) = D_80174158;
    func_80047784(arg2,
                  D_80174158[((D_80083228[0] +
                               *(s16 *)((s8 *)arg3 + 0x2A) + 0x100) >> 9) & 7],
                  0);
    direction_x = D_8006CCD8;
    direction *= 2;
    arg1[0] -= *(s16 *)((u8 *)direction_x + direction) << 19;
    arg1[1] -= *(s16 *)((u8 *)D_8006CCE8 + direction) << 19;
}
