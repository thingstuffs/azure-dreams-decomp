#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon.h"
#include "dungeon/player/object.h"



#include "dungeon/monster/dragon/transition_effect.h"
extern s32 find_active_rect_containing_point(s32, s32);
extern void advance_stored_entity_path(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, void *path_state);
extern void choose_arachne_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
extern void func_80173AC0(void *, void *, void *, void *);

#include "dungeon/monster/battnel.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"
#include "dungeon/level.h"
#include "dungeon/monster/battnel_frames.h"

extern u8 D_80173D14[];
extern u8 D_80173D1C[];
extern u8 D_80173D3C[];
extern u8 D_80173D4C[];

/* Update actor behavior, facing, and animation from dungeon state. */
/* Selects Battnel's movement, attacks, spells, and turn processing, with a ten-tick transition back to its
 * idle frames. */
void update_actor_behavior_facing_and_animation_2(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status) {
    u8 *anim_table;
    s32 room_id;
    u16 direction_aux;
    s16 anim_ticks;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        actor->action_id = 0xE;
        advance_stored_entity_path(actor, context, sprite, status);
        return;
    }

    if (status->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (sprite->frameTable == D_80173D4C) {
            return;
        }
        (sprite->frameTable) = battnel_frame_set;
        select_sprite_entry(sprite,
            battnel_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (status->flags1C & 0x200) {
        if (sprite->frameTable == D_80173D4C) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            status->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, battnel_frame_set)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (status->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }

        if (actor->action_id != 0xE) {
            u8 next_state = 0xE;

            if (sprite->frameTable != battnel_direction_frames) {
                s32 anim_delay = 10;

                actor->unk_A4.halves.low.s = anim_delay;
                (sprite->frameTable) = D_80173D14;
                select_sprite_entry(sprite,
                    D_80173D14[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->action_id = next_state;
        }

        actor->action_state_flags &= 0xFFF3;
        if (status->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80173D1C)) {
                return;
            }
        }

        if (status->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            func_80173AC0(actor, context, sprite, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (status->pending_turn_updates > 0) {
        if (status->flags1C & 0x20) {
            update_actor_status_and_mp(status);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            choose_arachne_move(actor, context, sprite, status);
            return;
        }
        if (!(status->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = NODE_BODY(previous_node);
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(status,
                        previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)update_entity_state_from_query(actor, context, sprite, 0) == 0) {
                return;
            }
            status->action_flags |= 0x4000;
            if (!(status->action_flags & 0x8000)) {
                choose_arachne_move(actor, context, sprite, status);
                return;
            }
        }

        switch ((status->action_flags & 0x3FFF) - 1) {
        case 7:
        case 8:
            if ((s16)check_actor_transition_and_start_effect(actor, context, sprite, status) == 0) {
                start_directional_actor_effect(actor, context, sprite, status);
            }
            return;

        case 4:
        case 5:
        case 6:
            {
                ActorRecord *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                global_actor = primary_actor_record;
                status->facing = direction;
                if (global_actor->action_id == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
                    return;
                }
            }

        case 11:
            update_actor_status_and_mp(status);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
            return;

        case 3:
        case 9:
        case 10:
        default:
            choose_arachne_move(actor, context, sprite, status);
            return;

        }
    }

    if (!(status->flags1C & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(status->flags1C & 0x430)) {

                if ((s16)test_neighbor_position_relation(sprite->tile_x,
                    sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y) != 0) {
                    status->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = battnel_direction_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    anim_ticks = actor->unk_A4.halves.low.u - 1;
    actor->unk_A4.halves.low.s = anim_ticks;
    if (anim_ticks > 0) {
        return;
    }
    actor->unk_A4.halves.low.s = -1;

    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7],
        0);
}
