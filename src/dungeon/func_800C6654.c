#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad[6];
    u16 count;
} S_80083460;

extern S_80083460 D_80083460;
extern u32 D_800814A0[3];
extern u8 *D_800E3D7C[];
extern u8 D_800E1B08[];
extern u8 D_800E1B2E[];

extern void func_800997FC();
extern s32 func_80042900(void *, s32, void *);
extern void func_800419EC(s32, s32);
extern void func_800A56E0(s32);

/* Advances a timed Z transition, waits for readiness, and marks completion. */
void func_800CBDB4(s16 *transition) {
    struct S_80083178 *state = &D_80083178;
    s16 phase = transition[1];

    if (phase == 1) {
        goto wait_ready;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto move_out;
        }
        goto done;
    }
    if (phase == 2) {
        goto move_back;
    }
    goto done;

move_out:
    state->state_94.v[1].z = state->state_94.v[1].z + (0x800 - state->state_94.v[1].z) / transition[2];
    {
        u16 frames_left = (u16)transition[2] - 1;
        transition[2] = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            goto done;
        }
        {
            S_80083460 *settings = &D_80083460;
            transition[1] = (u16)transition[1] + 1;
            state->state_94.v[1].z = -0x800;
            settings->count = (u16)settings->count - 1;
            func_800997FC(D_800E1B08, settings, state);
        }
    }
    goto done;

wait_ready:
    {
        S_80083460 *settings = &D_80083460;
        if ((settings->flags & 0x10) &&
            ((func_80042900(D_800E3D7C[0], 0x1C, state) << 16) == 0)) {
            transition[2] = 0x10;
            transition[1] = (u16)transition[1] + 1;
            settings->count = (u16)settings->count + 1;
            func_800419EC(0x10, 8);
            func_800A56E0(0x818);
        }
    }
    goto done;

move_back:
    state->state_94.v[1].z = state->state_94.v[1].z + (0 - state->state_94.v[1].z) / transition[2];
    {
        u16 frames_left = (u16)transition[2] - 1;
        transition[2] = frames_left;
        if ((s32)(frames_left << 16) <= 0) {
            S_80083460 *settings = &D_80083460;
            u8 *message = D_800E1B2E;
            settings->count = (u16)settings->count - 1;
            state->state_94.v[1].z = 0;
            func_800997FC(message);
            ((u16 *)transition)[-1] = ((u16 *)transition)[-1] | 0x8000;
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }

done:
    return;
}
