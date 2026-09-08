#include "common.h"

extern s32 D_800814A0[3];

/* Advance motion, rotation, and counters, flagging completion after the time limit. */
void func_81898824(void *state, void *motion, void *transform)
{
    u16 tick_count;
    void *linked_state;

    linked_state = *(void **)((s8 *)state + 0xC);
    *(u16 *)((s8 *)linked_state + 0x14) =
        (u16)(*(u16 *)((s8 *)linked_state + 0x14) + 1);
    *(s32 *)((s8 *)motion + 0x00) =
        *(s32 *)((s8 *)motion + 0x00) + *(s32 *)((s8 *)motion + 0x0C);
    *(s32 *)((s8 *)motion + 0x04) =
        *(s32 *)((s8 *)motion + 0x04) + *(s32 *)((s8 *)motion + 0x10);
    *(s32 *)((s8 *)motion + 0x08) =
        *(s32 *)((s8 *)motion + 0x08) + *(s32 *)((s8 *)motion + 0x14);
    *(u16 *)((s8 *)transform + 0x1A) =
        (u16)(*(u16 *)((s8 *)transform + 0x1A) + 0x300);
    tick_count = *(u16 *)((s8 *)state + 0x10) + 1;
    *(u16 *)((s8 *)state + 0x10) = tick_count;
    if (*(s16 *)((s8 *)state + 0x12) < (s16)tick_count) {
        *(u16 *)((s8 *)state - 2) =
            (u16)(*(u16 *)((s8 *)state - 2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
