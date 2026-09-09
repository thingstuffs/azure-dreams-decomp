#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_809A0B58_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[2];
    u16 unk_92;
    u8 pad_94[6];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[2];
    s16 unk_9E;
    u8 pad_A0[2];
    u16 unk_A2;
    u8 pad_A4[0xC];
    u16 unk_B0;
    u16 unk_B2;
} S_func_809A0B58_0;

typedef struct S_func_809A0B58_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_809A0B58_1;

typedef struct S_func_809A0B58_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union {
        u16 unk_00;
        s16 unk_00_s;
    } unk_2A;
} S_func_809A0B58_2;

typedef struct S_func_809A0B58_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_809A0B58_3;

extern M2C_UNK func_80047784();
extern M2C_UNK func_8009A350();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80175EA8[9];

/* Advance the counter when unblocked and reset the action when it exceeds 60. */
void func_809A0B58(S_func_809A0B58_0 *actor_state, void *unused, S_func_809A0B58_1 *sprite, S_func_809A0B58_2 *entity) {
    u16 tile_flags;
    u16 counter_value;
    u8 *direction_frames;
    S_func_809A0B58_3 *global_state;

    func_8009A350(sprite->unk_24 - 1, sprite->unk_25,
                  ((u16)entity->unk_2A.unk_00 >> 9) & 7, &tile_flags);
    if (!(tile_flags & 0x8400)) {
        counter_value = actor_state->unk_B2 + 1;
        actor_state->unk_B2 = counter_value;
        if ((u32)(counter_value & 0xFFFF) >= 0x3D) {
            global_state = (S_func_809A0B58_3 *)&D_80083460;
            actor_state->unk_B2 = 0x3C;
            global_state->unk_0A =
                (u16)(global_state->unk_0A + 1);
            actor_state->unk_9A = 0x19;
            actor_state->unk_8C = 0;
            actor_state->unk_9B = 0;
            direction_frames = D_80175EA8;
            *(u8 **)((u8 *)sprite + 0x2C) = direction_frames;
            func_80047784(sprite,
                           direction_frames[((s32)(D_80083228 + entity->unk_2A.unk_00_s + 0x100) >> 9) & 7],
                           0);
            actor_state->unk_B0 = (u16)entity->unk_2A.unk_00;
            entity->unk_1C = (s32)(entity->unk_1C & 0xFFFBFFFF);
            counter_value = actor_state->unk_92 - actor_state->unk_A2;
            actor_state->unk_A2 = 0;
            actor_state->unk_9E = 0;
            actor_state->unk_92 = counter_value;
        }
    }
}

