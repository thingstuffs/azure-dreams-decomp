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

void func_800CBDB4(s16 *arg0) {
    struct S_80083178 *state = &D_80083178;
    s16 kind = arg0[1];

    if (kind == 1) {
        goto kind1;
    }
    if (kind < 2) {
        if (kind == 0) {
            goto kind0;
        }
        goto done;
    }
    if (kind == 2) {
        goto kind2;
    }
    goto done;

kind0:
    state->state_94.v[1].z = state->state_94.v[1].z + (0x800 - state->state_94.v[1].z) / arg0[2];
    {
        u16 count = (u16)arg0[2] - 1;
        arg0[2] = count;
        if ((s32)(count << 16) > 0) {
            goto done;
        }
        {
            S_80083460 *settings = &D_80083460;
            arg0[1] = (u16)arg0[1] + 1;
            state->state_94.v[1].z = -0x800;
            settings->count = (u16)settings->count - 1;
            func_800997FC(D_800E1B08, settings, state);
        }
    }
    goto done;

kind1:
    {
        S_80083460 *settings = &D_80083460;
        if ((settings->flags & 0x10) &&
            ((func_80042900(D_800E3D7C[0], 0x1C, state) << 16) == 0)) {
            arg0[2] = 0x10;
            arg0[1] = (u16)arg0[1] + 1;
            settings->count = (u16)settings->count + 1;
            func_800419EC(0x10, 8);
            func_800A56E0(0x818);
        }
    }
    goto done;

kind2:
    state->state_94.v[1].z = state->state_94.v[1].z + (0 - state->state_94.v[1].z) / arg0[2];
    {
        u16 count = (u16)arg0[2] - 1;
        arg0[2] = count;
        if ((s32)(count << 16) <= 0) {
            S_80083460 *settings = &D_80083460;
            u8 *message = D_800E1B2E;
            settings->count = (u16)settings->count - 1;
            state->state_94.v[1].z = 0;
            func_800997FC(message);
            ((u16 *)arg0)[-1] = ((u16 *)arg0)[-1] | 0x8000;
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }

done:
    return;
}
