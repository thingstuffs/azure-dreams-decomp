#include "shared/object_node.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"



extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_timed_effect_size_and_position(void *, void *, void *, void *);

#include "dungeon/monster/saber.h"

extern u8 saber_action_direction_frames[];

/* Advances the actor_in action state and updates its directional animation. */
void advance_actor_action_and_direction(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite_in, ActorRecord *actor_in) {
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        (sprite_in->frameTable) = saber_direction_frames_2;
        select_sprite_entry(sprite_in,
            saber_direction_frames_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->activity_counts.parts.pending_action_count =
                ((u16)counter_base->activity_counts.parts.pending_action_count) - 1;
        }
        action->action_phase.u++;
        return;

    case 1:
        if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (actor_in->hp_delta != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (actor_in->mp_value.parts.whole == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = actor_in->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                update_timed_effect_size_and_position(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_in->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor_in,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
                s8 coordinate = *(s8 *)&sprite_in->room_index;
                TileObject *origin = &reference_tile_object;
                s32 probe_result;

                if ((coordinate != origin->room_index) || (coordinate < 0)) {
                    probe_result = get_tile_chebyshev_distance(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result < 2) {
                        if (!(generate_random_value(actor_in) & 7)) {
                            clear_slots_of_type(actor_in, STATUS_SLEEP);
                        }
                        actor_to_check = actor_in;
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        clear_slots_of_type(actor_in, STATUS_SLEEP);
                    }
                    actor_to_check = actor_in;
                }
            } else {
                actor_to_check = actor_in;
            }
            if ((get_entity_effect_value(actor_to_check, STATUS_SLEEP) << 16) != 0) {
                return;
            }

            (sprite_in->frameTable) = saber_action_direction_frames;
            select_sprite_entry(sprite_in,
                saber_action_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
                0);
            if (sprite_in->flags & 0x8000) {
                action->unk_8C.address = &saber_behavior_entry;
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count++;

            action->action_phase.u++;
            return;
        }
        (sprite_in->frameTable) = saber_action_direction_frames;
        select_sprite_entry(sprite_in,
            saber_action_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
            0);
        if (sprite_in->flags & 0x8000) {
            action->unk_8C.address = &saber_behavior_entry;
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count++;

        action->action_phase.u++;
        return;

    case 2:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        action->unk_8C.address = &saber_behavior_entry;

        return;
    }
}
