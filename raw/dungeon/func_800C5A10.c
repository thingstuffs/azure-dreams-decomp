#include "common.h"

typedef struct {
    u8 pad_00[0x96];
    u16 value_96;
    u8 pad_98[3];
    u8 state_9b;
    u8 pad_9c[0x16];
    u16 value_b2;
} State;

typedef struct {
    u8 pad_00[0x14];
    s32 value_14;
} Position;

typedef struct {
    u8 pad_00[0xc];
    u8 pad_0c;
    u8 pad_0d;
    u8 value_0e;
    u8 pad_0f[0xd];
    u16 value_1c;
    u16 value_1e;
} Motion;

extern u16 D_80083460[];
extern s32 D_800814A0[];

extern s32 func_800644B8(s32 arg0);
extern s32 func_8009A028(void *arg0);
extern s32 func_800A2C78(void *arg0);
extern s32 func_800A32A4(void *arg0);

void func_800CB170(State *state, Position *position, Motion *motion, void *arg3) {
    u16 value;
    u8 value_0e;
    s32 one = 1;

    {
        s32 current_state = state->state_9b;
        if (current_state != one) {
            if (current_state < 2) {
                if (current_state == 0) {
                    goto state_zero;
                }
                goto done;
            }
            if (current_state != 2) {
                goto done;
            }
            goto state_two;
        }
        goto state_one;
    }

state_zero:
    if ((func_800A2C78(arg3) << 16) == 0) {
        u16 *global_83460;
        global_83460 = &D_80083460[0];
        global_83460[5] = global_83460[5] + 1;
        state->value_b2 = 4;
        state->value_96 = 0;
        state->state_9b = state->state_9b + 1;
        goto state_one;
    }
    goto done;

state_one:
    {
        value = state->value_96 + 1;
        state->value_96 = value;
        motion->value_1c = motion->value_1c + func_800644B8((value << 16) >> 11);
        motion->value_1e = motion->value_1e - func_800644B8((s16)state->value_96 << 5);
        value = state->value_b2 - 1;
        state->value_b2 = value;
        if ((value << 16) <= 0) {
            state->state_9b = state->state_9b + 1;
        }
        goto done;
    }

state_two:
    value = state->value_96 - 1;
    state->value_96 = value;
    if ((value << 16) <= 0) {
        state->value_96 = one;
    }
    motion->value_1c = motion->value_1c - func_800644B8((s16)state->value_96 << 5) * 2;
    motion->value_1e = motion->value_1e + func_800644B8((s16)state->value_96 << 5) * 4;
    position->value_14 = position->value_14 + (s32)0xfffe0000;
    value_0e = motion->value_0e - 4;
    motion->value_0e = value_0e;
    motion->pad_0d = value_0e;
    motion->pad_0c = value_0e;
    if ((s16)motion->value_1c <= 0) {
        u16 *global_83460;
        global_83460 = &D_80083460[0];
        global_83460[5] = global_83460[5] - 1;
        func_800A32A4(arg3);
        func_8009A028(arg3);
        ((u16 *)arg3)[-1] = ((u16 *)arg3)[-1] | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    return;
}
