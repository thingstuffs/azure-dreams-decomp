#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Advance the accumulation step, update the target, and flag completion past the final step. */
void func_81892A0C(void *step_state, void *accumulator, void *target)
{
    void *owner;
    s32 total;
    s32 increment;

    owner = *(void **)step_state;
    *(u16 *)((u8 *)owner + 0x14) += 1;
    *(u16 *)((u8 *)step_state + 4) += 1;

    total = *(s32 *)((u8 *)accumulator + 8);
    increment = *(s32 *)((u8 *)accumulator + 0x14);
    *(s32 *)((u8 *)accumulator + 8) = total + increment;
    if (*(s16 *)((u8 *)step_state + 4) < 8) {
        *(s32 *)((u8 *)accumulator + 0x14) *= 2;
    }

    if (*(s16 *)((u8 *)step_state + 4) == *(s16 *)((u8 *)step_state + 6)) {
        *(u16 *)((u8 *)target + 0x1E) >>= 1;
    }

    func_800478B8(target);

    if (*(s16 *)((u8 *)step_state + 4) > *(s16 *)((u8 *)step_state + 6)) {
        *(u16 *)((u8 *)step_state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
