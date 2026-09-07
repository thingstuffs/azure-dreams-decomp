#include "common.h"

extern s32 D_80100E40;

void func_800AAFE0(void *arg0, s32 arg1) {
    s8 *base;
    s8 *p;

    base = (s8 *)&D_80100E40;
    p = base + (arg1 * 8);
    *(u16 *)((s8 *)arg0 + 2) = *(u16 *)(p + 0);
    *(u16 *)((s8 *)arg0 + 6) = *(u16 *)(p + 2);
    *(u16 *)((s8 *)arg0 + 10) = *(u16 *)(p + 4);
}
