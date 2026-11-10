#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"
#include "dungeon.h"
#include "dungeon/level.h"

#include "dungeon/player/object/action_state.h"
extern void update_actor_status_and_mp(ActorRecord *entity);

#include "dungeon/monster/saber.h"
#include "dungeon/actor.h"
#include "dungeon/monster/viper.h"

extern u8 saber_action_direction_frames[];


/* Updates actor state, directional animation, and the shared transition counter. */
void update_actor_directional_animation(ActorRecord *actor_in, ObjectPosition *position, SpriteFrameState *target, ActorRecord *entity_in) {
    ActorRecord *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = actor_in->action_phase;
    switch (state) {
    case 0:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    target->frameTable = saber_direction_frames_2;
    direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target, saber_direction_frames_2[direction & 7], 0);
    actor_in->action_phase++;
    return;

    case 1:
    if (entity->mp_value.parts.whole != 0) {
        DungeonGlobalStatus *shared_counter;

        target->frameTable = saber_action_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, saber_action_direction_frames[direction & 7], 0);
        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count++;
        actor_in->action_phase++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_in, position, target, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor_in, position, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, position, target, entity);
            update_timed_effect_size_and_position(actor_in, position, target, entity);
            return;
        }
        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            {
                ObjectNodeHeader *previous_node;
                void *previous_body;
                ActorRecord *previous_actor;

                previous_node = primary_actor_record->previous_actor_header;
                previous_body = NODE_BODY(previous_node);
                previous_actor = previous_body;
                if ((check_entity_relation(entity,
                        previous_actor) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(entity);
        } else {
            update_actor_status_and_mp(entity);
        }
        on_actor_status_updated(entity);
        if (entity->mp_value.parts.whole == 0) {
            return;
        }
        target->frameTable = saber_action_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, saber_action_direction_frames[direction & 7], 0);
        shared_state->activity_counts.parts.pending_action_count++;
    }
    actor_in->action_phase++;
    return;

    case 2:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    actor_in->unk_8C.address = &saber_behavior_entry;

    return;
    default:
        return;
    }
}
