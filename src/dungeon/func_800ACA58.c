#include "common.h"

extern void func_800478B8(s32);
extern struct { s32 unk0; s32 pad[2]; } D_800814A0;

/* Advances the accumulator and decrements the counter, setting flags on underflow. */
void func_800B21B8(void *counter_state, void *accumulator, s32 update_arg) {
    s16 remaining;

    *((s32 *) accumulator + 2) = *((s32 *) accumulator + 2) + 0x8000;
    func_800478B8(update_arg);
    remaining = *(u16 *) ((u8 *) counter_state + 6) - 1;
    *(u16 *) ((u8 *) counter_state + 6) = remaining;
    if (remaining < 0) {
        *(u16 *) ((u8 *) counter_state - 2) |= 0x8000;
        D_800814A0.unk0 = D_800814A0.unk0 | 0x8000;
    }
}
