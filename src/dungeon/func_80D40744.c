#include "common.h"

typedef struct S_func_80D40744_0 {
    u8 pad_00[0x6D];
    u8 unk_6D;
    u8 pad_6E[3];
    u8 unk_71;
    u8 pad_72[0x1A];
    s32 unk_8C;
    u8 pad_90[6];
    s16 unk_96;
    u8 pad_98[2];
    union {
        u8 u8;
        s8 s8;
    } unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x15];
    s8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
} S_func_80D40744_0;

typedef struct S_func_80D40744_1 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[6];
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    void *unk_0C;
    void *unk_10;
} S_func_80D40744_1;

extern void func_800A4ACC(void *);
extern s32 D_80083460;
extern u16 D_80083462;

/* Initializes an entity action when the global state permits it. */
void func_80175F44(S_func_80D40744_0 *entity, s32 unused_1, s32 unused_2, s32 unused_3, s32 requested_mode)
{
    s32 state_or_flags;
    S_func_80D40744_0 *saved_entity = entity;
    u8 flags_71 = ((volatile S_func_80D40744_0 *)entity)->unk_71;
    s32 initial_mode = requested_mode;
    u16 raw_mode;

    flags_71 &= 0x7F;
    raw_mode = initial_mode;
    initial_mode = (s16)initial_mode;
    entity->unk_71 = flags_71;
    if (initial_mode != 2) {
        S_func_80D40744_1 *state = (S_func_80D40744_1 *)&D_80083460;

        state_or_flags = state->unk_02;
        if (state_or_flags & 0x2000) {
            goto reject_saved;
        }
        if (state->unk_0C == entity) {
            goto accepted;
        }
        if (state->unk_0C != 0) {
            goto reject_entity;
        }
        if (state->unk_10 != 0) {
            goto reject_entity;
        }
        if (!(state_or_flags & 8)) {
            goto accepted;
        }

reject_entity:
        entity->unk_9A.u8 = 14;
        goto done;
    }

    state_or_flags = (s32)&D_80083460;
    if (((S_func_80D40744_1 *)state_or_flags)->unk_02 & 0x2000) {
        goto reject_saved;
    }
    if (((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 == 0) {
        goto increment_state;
    }

reject_saved:
    saved_entity->unk_9A.u8 = 14;
    goto done;

increment_state:
    ((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 =
        (u16)((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 + 1;

accepted:
    {
        s32 mode = (s16)raw_mode;

        if (mode == 0) {
            S_func_80D40744_1 *state = (S_func_80D40744_1 *)((u8 *)&D_80083462 - 2);
            state->unk_0A.u16++;
        }
        entity->unk_8C = 0;
        entity->unk_9A.s8 = 0x19;
        entity->unk_9B = 0;
        entity->unk_96 = 0;
        entity->unk_B3 = 0;
        entity->unk_B1 = 0;
        entity->unk_B2 = 0;
        entity->unk_B4 = raw_mode;
        if (mode == 0) {
            func_800A4ACC(saved_entity);
            saved_entity->unk_6D--;
        }
    }

done:
    return;
}

