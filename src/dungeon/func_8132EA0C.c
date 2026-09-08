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

/* Advance the position and timer, setting completion flags when the timer expires. */
void func_80165A0C(void *state, Position *pos, s32 handle)
{
    s32 dy;
    s32 dz;
    u16 timer;

    dy = pos->dy;
    dz = pos->dz;
    pos->x += pos->dx;
    pos->y += dy;
    pos->z += dz;
    func_800478B8(handle, pos, dy, dz);
    func_800478B8(handle);
    timer = *(u16 *)((u8 *)state + 0x32) - 1;
    *(u16 *)((u8 *)state + 0x32) = timer;
    if ((timer << 16) <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
