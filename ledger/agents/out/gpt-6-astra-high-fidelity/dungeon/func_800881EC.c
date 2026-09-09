#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void func_80094E34(u8 *a0);
extern void func_80048A44(void *a0, s16 a1, s16 a2, s32 a3);

extern s16 D_80083228;
extern s16 D_80083460[];
extern u8 D_800DCFF0[8];

void func_8008D94C(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u16 flags;
    s32 idx;
    register u8 *table ASM_REG("$4"); /* MATCH: retail keeps the table base in a0 until the final call. */

    flags = *(u16 *)(arg0 + 0xA2);
    *(s8 *)(arg0 + 0x9A) = 0x24;
    *(s8 *)(arg0 + 0x9B) = 0;
    *(void **)(arg0 + 0x8C) = NULL;
    *(u16 *)(arg0 + 0xA2) = flags & 0xFEFF;
    func_80094E34(arg0);

    D_80083460[2] = D_80083460[2] * 2;
    table = &D_800DCFF0[0];
    *(u8 **)(arg2 + 0x2C) = table;

    idx = ((D_80083228 + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
    func_80048A44(arg2, table[idx], 0, 1);
}
