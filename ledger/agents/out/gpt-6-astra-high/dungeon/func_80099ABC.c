#include "common.h"

typedef struct {
    u8 value0;
    u8 value1;
    u8 value2;
    u8 pad03[0x17];
    s16 state;
    u16 counter;
    u8 pad20[8];
    s32 flags;
    u8 pad2c[2];
    s16 mode;
} InterpState;

typedef struct {
    u8 pad00[0x0c];
    u8 value0;
    u8 value1;
    u8 value2;
    u8 pad0f[0x0d];
    u16 counter;
    u16 counter_copy;
} InterpTarget;

typedef struct {
    s32 first;
    u8 pad04[0x2968];
    s32 last;
} E296C;

extern u8 D_80044BB0[];
extern E296C D_800E296C;
extern s32 D_800814A0[3];
extern void func_8004491C(void *, u8 *);
extern void func_800A56E0(s32);

/* Interpolate target values after a delay, then reduce its counter to zero and update flags. */
void func_8009F21C(InterpState *state, void *unused, InterpTarget *target) {
    u16 ticks_left;
    u16 target_counter;
    E296C *global_state;
    s32 *status_flags;
    s32 prior_flags;
    s32 state_flags;
    s32 merged_flags;
    s32 cleared_flags;

    if (state->state == 0) {
        ticks_left = state->counter - 1;
        state->counter = ticks_left;
        if ((s16)ticks_left <= 0) {
            func_8004491C((u8 *)state - 0x20, D_80044BB0);
            state->counter = 8;
            state->state++;
            func_800A56E0(0x80F);
        }
    } else if (state->state == 1) {
        target->value0 += (state->value0 - target->value0) / (s16)state->counter;
        target->value1 += (state->value1 - target->value1) / (s16)state->counter;
        target->value2 += (state->value2 - target->value2) / (s16)state->counter;
        ticks_left = state->counter - 1;
        state->counter = ticks_left;
        if ((s16)ticks_left <= 0) {
            *(u32 *)((u8 *)target + 0x0c) = *(u32 *)state;
            state->counter = 0x10;
            state->state++;
            goto done;
        }
    } else {
        target_counter = target->counter;
        target_counter -= target_counter / (s16)state->counter;
        target->counter = target_counter;
        target->counter_copy = target_counter;
        ticks_left = state->counter - 1;
        state->counter = ticks_left;
        if ((s16)ticks_left <= 0) {
            global_state = &D_800E296C;
            prior_flags = global_state->first;
            state_flags = state->flags;
            merged_flags = prior_flags | state_flags;
            global_state->first = merged_flags;
            *(u16 *)((u8 *)state - 2) |= 0x8000;
            status_flags = D_800814A0;
            status_flags[0] |= 0x8000;
            if (state->mode == 0) {
                cleared_flags = merged_flags & 0xFFFBFFFF;
                global_state->first = cleared_flags;
            }
        }
    }

done:
    return;
}
