#include "common.h"

extern s32 func_800B28A0(void);
extern u16 D_800D4244[];

void func_800C0FE4(void *arg0) {
    s32 index;
    u16 *base;
    u16 *p;

    index = func_800B28A0();
    base = D_800D4244;
    p = base + (index * 2);
    ((u16 *)arg0)[2] = p[0];
    ((u16 *)arg0)[3] = p[1];
}
