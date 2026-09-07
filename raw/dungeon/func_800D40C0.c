#include "common.h"

extern void func_8003DB94(void *arg0, s32 arg1, s32 arg2);
extern s16 D_80083228;
extern u8 D_800E260C[];

void func_800D9820(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 idx;

    *((u8 *)arg0 + 0x9A) = 0x10;
    *((u8 *)arg0 + 0x9B) = 0;
    *(u8 **)((u8 *)arg2 + 0x2C) = D_800E260C;
    idx = ((D_80083228 + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 7) & 0x1C;
    func_8003DB94(arg2, *(s32 *)(D_800E260C + idx), 0);
}
