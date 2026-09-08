#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(p, t, n) (*(t)((u8 *)(p) + (n)))

extern M2C_UNK func_80047784();
extern M2C_UNK func_8009A350();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80175EA8[9];

/* Advance the counter when unblocked and reset the action when it exceeds 60. */
void func_809A0B58(void *actor_state, void *unused, void *sprite, void *entity) {
    u16 tile_flags;
    u16 counter_value;
    u8 *direction_frames;
    u8 *global_state;

    func_8009A350(FIELD(sprite, u8 *, 0x24) - 1, FIELD(sprite, u8 *, 0x25),
                  ((u16)FIELD(entity, u16 *, 0x2A) >> 9) & 7, &tile_flags);
    if (!(tile_flags & 0x8400)) {
        counter_value = FIELD(actor_state, u16 *, 0xB2) + 1;
        FIELD(actor_state, u16 *, 0xB2) = counter_value;
        if ((u32)(counter_value & 0xFFFF) >= 0x3D) {
            global_state = (u8 *)&D_80083460;
            FIELD(actor_state, u16 *, 0xB2) = 0x3C;
            FIELD(global_state, u16 *, 0xA) =
                (u16)(FIELD(global_state, u16 *, 0xA) + 1);
            FIELD(actor_state, s8 *, 0x9A) = 0x19;
            FIELD(actor_state, s32 *, 0x8C) = 0;
            FIELD(actor_state, s8 *, 0x9B) = 0;
            direction_frames = D_80175EA8;
            FIELD(sprite, u8 **, 0x2C) = direction_frames;
            func_80047784(sprite,
                           direction_frames[((s32)(D_80083228 + FIELD(entity, s16 *, 0x2A) + 0x100) >> 9) & 7],
                           0);
            FIELD(actor_state, u16 *, 0xB0) = (u16)FIELD(entity, u16 *, 0x2A);
            FIELD(entity, s32 *, 0x1C) = (s32)(FIELD(entity, s32 *, 0x1C) & 0xFFFBFFFF);
            counter_value = FIELD(actor_state, u16 *, 0x92) - FIELD(actor_state, u16 *, 0xA2);
            FIELD(actor_state, u16 *, 0xA2) = 0;
            FIELD(actor_state, s16 *, 0x9E) = 0;
            FIELD(actor_state, u16 *, 0x92) = counter_value;
        }
    }
}

