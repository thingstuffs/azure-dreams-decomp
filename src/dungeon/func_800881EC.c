#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void func_80094E34(void);
extern void func_80048A44(void *a0, s16 a1, s16 a2, s32 a3);

extern s16 D_80083228;
extern s16 D_80083460[];
extern u8 D_800DCFF0[8];

void func_8008D94C(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u16 flags;
    s32 idx;

    flags = *(u16 *)(arg0 + 0xA2);
    *(s8 *)(arg0 + 0x9A) = 0x24;
    *(s8 *)(arg0 + 0x9B) = 0;
    *(void **)(arg0 + 0x8C) = NULL;
    *(u16 *)(arg0 + 0xA2) = flags & 0xFEFF;
    func_80094E34();

    D_80083460[2] = D_80083460[2] * 2;
    *(u8 **)(arg2 + 0x2C) = &D_800DCFF0[0];

    idx = ((D_80083228 + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
    func_80048A44(arg2, D_800DCFF0[idx], 0, 1);
}
