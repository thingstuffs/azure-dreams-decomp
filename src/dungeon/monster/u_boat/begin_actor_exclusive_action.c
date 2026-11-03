#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/monster/u_boat.h"
#include "dungeon/actor.h"





/*
 * Claims an exclusive U-Boat action when dungeon activity allows it; otherwise selects idle state
 * 14.
 */
void begin_actor_exclusive_action(ActorRecord *entity, ObjectPosition *unused_1, SpriteFrameState *unused_sprite, s32 unused_3, s32 requested_mode)
{
    s32 state_or_flags;
    ActorRecord *saved_entity = entity;
    u8 flags_71 = entity->movement_queue_state;
    s32 initial_mode = requested_mode;
    u16 raw_mode;

    flags_71 &= 0x7F;
    raw_mode = initial_mode;
    initial_mode = (s16)initial_mode;
    entity->movement_queue_state = flags_71;
    if (initial_mode != 2) {
        DungeonGlobalStatus *state = &g_dungeon_status;

        state_or_flags = state->flags;
        if (state_or_flags & 0x2000) {
            saved_entity->action_id.u = 14;
            return;
        }
        if (state->active_actor != entity) {
            if (state->active_actor != 0 || state->pending_display_owner != 0 || (state_or_flags & 8)) {
                entity->action_id.u = 14;
                return;
            }
        }
    } else {
        state_or_flags = (s32)&g_dungeon_status.turn_scale;
        if ((((DungeonGlobalStatus *)state_or_flags)->flags & 0x2000) ||
            ((DungeonGlobalStatus *)state_or_flags)->activity_counts.parts.pending_action_count != 0) {
            saved_entity->action_id.u = 14;
            return;
        }
        ((DungeonGlobalStatus *)state_or_flags)->activity_counts.parts.pending_action_count =
            (u16)((DungeonGlobalStatus *)state_or_flags)->activity_counts.parts.pending_action_count + 1;
    }

    {
        s32 mode = (s16)raw_mode;

        if (mode == 0) {
            DungeonGlobalStatus *state = &g_dungeon_status;
            (*(u16 *)&state->activity_counts.parts.pending_action_count)++;
        }
        entity->unk_8C.word = 0;
        entity->action_id.s = 0x19;
        entity->action_phase.s = 0;
        entity->action_timer.s = 0;
        entity->unk_B0.signed_bytes[3] = 0;
        entity->unk_B0.signed_bytes[1] = 0;
        entity->unk_B0.signed_bytes[2] = 0;
        entity->unk_B4.signed_bytes[0] = raw_mode;
        if (mode == 0) {
            advance_status_timers(saved_entity);
            saved_entity->pending_turn_updates = (u8)saved_entity->pending_turn_updates - 1;
        }
    }

    return;
}

