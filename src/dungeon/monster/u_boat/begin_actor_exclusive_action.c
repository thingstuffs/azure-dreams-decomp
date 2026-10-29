#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/monster/u_boat.h"

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


/*
 * Claims an exclusive U-Boat action when dungeon activity allows it; otherwise selects idle state
 * 14.
 */
void begin_actor_exclusive_action(S_func_80D40744_0 *entity, ObjectPosition *unused_1, s32 unused_2, s32 unused_3, s32 requested_mode)
{
    s32 state_or_flags;
    S_func_80D40744_0 *saved_entity = entity;
    u8 flags_71 = entity->unk_71;
    s32 initial_mode = requested_mode;
    u16 raw_mode;

    flags_71 &= 0x7F;
    raw_mode = initial_mode;
    initial_mode = (s16)initial_mode;
    entity->unk_71 = flags_71;
    if (initial_mode != 2) {
        DungeonGlobalStatus *state = &g_dungeon_status;

        state_or_flags = state->flags;
        if (state_or_flags & 0x2000) {
            saved_entity->unk_9A.u8 = 14;
            return;
        }
        if (state->active_actor != entity) {
            if (state->active_actor != 0 || state->pending_display_owner != 0 || (state_or_flags & 8)) {
                entity->unk_9A.u8 = 14;
                return;
            }
        }
    } else {
        state_or_flags = (s32)&g_dungeon_status.turn_scale;
        if ((((S_func_80D40744_1 *)state_or_flags)->unk_02 & 0x2000) ||
            ((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 != 0) {
            saved_entity->unk_9A.u8 = 14;
            return;
        }
        ((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 =
            (u16)((S_func_80D40744_1 *)state_or_flags)->unk_0A.s16 + 1;
    }

    {
        s32 mode = (s16)raw_mode;

        if (mode == 0) {
            DungeonGlobalStatus *state = &g_dungeon_status;
            (*(u16 *)&state->activity_counts.parts.pending_action_count)++;
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
            advance_status_timers(saved_entity);
            saved_entity->unk_6D--;
        }
    }

    return;
}

