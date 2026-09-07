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

void func_8009F21C(InterpState *state, void *unused, InterpTarget *target) {
    u16 next;
    u16 target_counter;
    E296C *e296c;
    s32 *e814a0;
    s32 first;
    s32 flags;
    s32 combined;
    s32 masked;

    if (state->state == 0) {
        next = state->counter - 1;
        state->counter = next;
        if ((s16)next <= 0) {
            func_8004491C((u8 *)state - 0x20, D_80044BB0);
            state->counter = 8;
            state->state++;
            func_800A56E0(0x80F);
        }
    } else if (state->state == 1) {
        target->value0 += (state->value0 - target->value0) / (s16)state->counter;
        target->value1 += (state->value1 - target->value1) / (s16)state->counter;
        target->value2 += (state->value2 - target->value2) / (s16)state->counter;
        next = state->counter - 1;
        state->counter = next;
        if ((s16)next <= 0) {
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
        next = state->counter - 1;
        state->counter = next;
        if ((s16)next <= 0) {
            e296c = &D_800E296C;
            first = e296c->first;
            flags = state->flags;
            combined = first | flags;
            e296c->first = combined;
            *(u16 *)((u8 *)state - 2) |= 0x8000;
            e814a0 = D_800814A0;
            e814a0[0] |= 0x8000;
            if (state->mode == 0) {
                masked = combined & 0xFFFBFFFF;
                e296c->first = masked;
            }
        }
    }

done:
    return;
}
