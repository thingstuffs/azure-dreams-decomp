#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Position;

extern void func_800478B8();
extern s32 D_800814A0[3];

void func_80165A0C(void *arg0, Position *pos, s32 arg2)
{
    s32 dy;
    s32 dz;
    u16 timer;

    dy = pos->dy;
    dz = pos->dz;
    pos->x += pos->dx;
    pos->y += dy;
    pos->z += dz;
    func_800478B8(arg2, pos, dy, dz);
    func_800478B8(arg2);
    timer = *(u16 *)((u8 *)arg0 + 0x32) - 1;
    *(u16 *)((u8 *)arg0 + 0x32) = timer;
    if ((timer << 16) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: The Position fields preserve the four incoming argument roles across both calls,
   naturally yielding the retail 0x20 frame and s1/s0 holds for arg0/arg2.
   The u16 timer and direct flag updates reproduce the halfword CFG; cdk-G0 closes the code motion. */
