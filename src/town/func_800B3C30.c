#include "common.h"

extern s32 D_800B0824[];

void func_800B1390(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7) {
    *(s32 *)((s8 *)arg0 + 4) = 1;
    *(s32 *)((s8 *)arg0 + 8) = arg2;
    *(s32 *)((s8 *)arg0 + 0xC) = arg3;
    *(s32 *)((s8 *)arg0 + 0x20) = arg1;
    *(s32 **)((s8 *)arg0 - 0x10) = D_800B0824;
    *(s32 *)((s8 *)arg0 + 0x10) = arg4;
    *(s32 *)((s8 *)arg0 + 0x14) = arg5;
    *(s32 *)((s8 *)arg0 + 0x24) = arg6;
    *(s32 *)((s8 *)arg0 + 0x18) = arg7;
}
