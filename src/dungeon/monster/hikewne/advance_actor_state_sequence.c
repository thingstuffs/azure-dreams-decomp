#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon.h"
#include "dungeon/level.h"


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/hikewne_frames.h"

extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void update_actor_status_and_mp(void *);
extern void update_directional_sprite_state_and_signals(void *, void *, SpriteFrameState *, void *);

extern u8 D_801740F8[];

/* Advances the actor state sequence and selects effects for its facing direction. */
/* Animates Hikewne's status-slot-1 entry and recovery, updates MP and turns while active, then restores
 * its normal callback. */
void advance_actor_state_sequence(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor) {
    s32 effect_entry;
    s32 next_state;
    u8 state;

    state = action->action_phase;
    switch (state) {
    case 0:
    {
        u8 *local_table_0;
        {
            DungeonGlobalStatus *dungeon_state;
            if ((entity->flags & 0xE000) == 0) {
                return;
            }

            local_table_0 = D_801740F8;

            entity->frameTable = local_table_0;
            effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            effect_entry &= 7;
            effect_entry += (s32)local_table_0;
            select_sprite_entry(entity, *(u8 *)effect_entry, 0);
            dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)--;
            next_state = action->action_phase + 1;
            action->action_phase = next_state;
            return;
        }

    }

    case 1:
    {
        u8 *local_table_1;
        if (action->unk_90.parts.high.s != 0) {
            return;
        }
        local_table_1 = hikewne_frame_set_1;

        entity->frameTable = local_table_1;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_1;
        select_sprite_entry(entity, *(u8 *)effect_entry, 0);
        action->action_timer = 0;
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;

    }

    case 2:
    {
        u8 *local_table_2;
        if ((s16)action->action_timer++ < 2) {
            return;
        }
        local_table_2 = hikewne_frame_set_2;

        entity->frameTable = local_table_2;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_2;
        select_sprite_entry(entity, *(u8 *)effect_entry, 0);
        action->action_timer = 0;
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;

    }

    case 3:
    {
        u8 *local_table_3;
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->hp_delta != 0) &&
                begin_ready_actor_directional_action(action, context, entity, 0)) {
                return;
            }

            if (actor->mp_value.parts.whole == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                advance_actor_pending_action(action, context, entity, actor);
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                begin_pushed_actor_move(action, context, entity, actor);
                return;
            }

            {
                u32 adjustment_flag = 0x80000;
                if ((actor_flags & adjustment_flag) != 0) {
                    u16 remaining_amount;

                    begin_actor_move_to_target_facing(action, context, entity, actor);
                    remaining_amount = action->unk_90.parts.high.u;
                    remaining_amount -= action->unk_A0.parts.high;
                    action->unk_A0.parts.high = 0;
                    action->unk_9E = 0;
                    action->unk_90.parts.high.u = remaining_amount;
                    update_directional_sprite_state_and_signals(action, context, entity, actor);
                    return;
                }
            }

            if (actor->pending_turn_updates == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((s16)check_entity_relation(actor,
                        (u8 *)owner->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *room_base = &reference_tile_object;
                s8 room_id = ((s8)(entity->room_index));

                if ((room_id == room_base->room_index && room_id >= 0) || (s16)get_tile_chebyshev_distance(room_base, entity) < 2) {
                    if ((generate_random_value() & 7) == 0) {
                        clear_slots_of_type(actor, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }

        local_table_3 = hikewne_frame_set_3;

        entity->frameTable = local_table_3;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_3;
        select_sprite_entry(entity, *(u8 *)effect_entry, 0);
        if ((entity->flags & 0x8000) != 0) {
            break;
        }
        action->action_phase++;
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)++;
        }
        return;

    }

    case 4:
    {
        u8 *local_table_4;
        u32 phase_flag = 0x40000;
        u32 phase_flags;

        if ((entity->flags & 0xE000) == 0) {
            return;
        }

        local_table_4 = D_801740F8;
        phase_flags = ((u32)actor->flags1C);

        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
        entity->frameTable = local_table_4;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_4;
        select_sprite_entry(entity, *(u8 *)effect_entry, 0);
        action->action_timer = 0;
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;
    }

    case 5:
    {
        u8 *local_table_5;
        if ((s16)action->action_timer++ < 4) {
            return;
        }

        local_table_5 = hikewne_frame_set;

        entity->frameTable = local_table_5;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_5;
        select_sprite_entry(entity, *(u8 *)effect_entry, 0);
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)--;
        }
        break;

    }
    default:
        return;
    }

    action->unk_8C.address = update_actor_behavior_animation_and_facing;
    return;
}
