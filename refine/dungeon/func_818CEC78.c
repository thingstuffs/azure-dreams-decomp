#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_80025924[5];
extern s32 D_800814A0[3];

/* Advance position and object state, then flag completion on timeout or object status. */
void func_818CEC78(void *state, void *position, void *object)
{
    s32 position_z;
    s32 step_z;
    u16 ticks_left;

    *(s32 *)((u8 *)position + 0) += *(s32 *)((u8 *)state + 0x4C);
    *(s32 *)((u8 *)position + 4) += *(s32 *)((u8 *)state + 0x50);
    position_z = *(s32 *)((u8 *)position + 8);
    step_z = *(s32 *)((u8 *)state + 0x54);
    D_80025924[0] = 1;
    *(s32 *)((u8 *)position + 8) = position_z + step_z;
    func_800478B8(object);

    *(u16 *)((u8 *)object + 0x1C) += 0x80;
    *(u16 *)((u8 *)object + 0x1E) += 0x80;

    ticks_left = *(u16 *)((u8 *)state + 2) - 1;
    *(u16 *)((u8 *)state + 2) = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (*(u16 *)((u8 *)object + 0x14) & 0x8000) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
