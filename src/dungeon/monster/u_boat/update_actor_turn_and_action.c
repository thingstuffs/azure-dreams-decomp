#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/monster/u_boat_frames.h"
#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/effect/shade.h"



#include "dungeon/item/find_active_rect_containing_point_api.h"
#include "dungeon/monster/u_boat.h"



extern u8 D_800E2418[];


#include "dungeon/monster/u_boat.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

/* Updates dungeon actor animation, status, and action dispatch. */
void update_actor_turn_and_action(ActorRecord *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        entity->action_id = 0xE;
        advance_aura_actor_turn_path(entity, context, sprite, actor);
        return;
    }

    if (actor->mp_value.parts.whole == 0) {
        if (entity->unk_B4.bytes[1] == 0) {
            void *anim_table;

            advance_actor_pending_action(entity, context, sprite, actor);
            if (sprite->frameTable == uboat_action_frames) {
                return;
            }
            anim_table = u_boat_frame_set;
            (sprite->frameTable) = anim_table;
            select_sprite_entry(sprite,
                ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        } else {
            begin_actor_exclusive_action(entity, context, sprite, 0, 0);
            return;
        }
    }

    if (((u32)actor->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == uboat_action_frames) {
            entity->action_id = 0xD;
            entity->action_phase = 1;
            entity->unk_8C.word = 0;
            actor->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, u_boat_frame_set) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(entity, context, sprite, actor);
            return;
        }

        if (entity->action_id != 0xE) {
            entity->action_id = 0xE;
        }
        if (entity->unk_B4.bytes[1] == 0) {
            void *anim_table = uboat_default_frames;
            u8 is_active;

            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
                sprite->frame_ticks = 1;
                is_active = entity->unk_B0.bytes[0];
                entity->unk_9E = 0;
                entity->unk_A0.parts.high = 0;
            } else {
                is_active = entity->unk_B0.bytes[0];
            }
            if (is_active == 0) {
                create_owner_linked_directional_object(entity, context, sprite);
            }
            if (entity->unk_B4.bytes[1] == 0) {
                actor->flags1C |= 0x40000;
                entity->action_state_flags &= 0xFFF7;
            }
        }

        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, uboat_ready_frames) != 0) {
                return;
            }
        }

        if (((u32)actor->flags1C) & ACTOR_LIFTED) {
            s16 height_delta;

            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            height_delta = entity->unk_90.parts.high - entity->unk_A0.parts.high;
            entity->unk_A0.parts.high = 0;
            entity->unk_9E = 0;
            entity->unk_90.parts.high = height_delta;
            update_actor_action_transition(entity, context, sprite, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(entity, context, sprite, actor);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x,
        sprite->tile_y);
    sprite->room_index = room_id;

    if (actor->pending_turn_updates > 0) {
        if (((u32)actor->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            choose_and_execute_actor_step(entity, context, sprite, actor);
            return;
        }
        if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = NODE_BODY(previous_node);
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((update_entity_state_from_query(entity, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = actor->action_flags | 0x4000;
            actor->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                choose_and_execute_actor_step(entity, context, sprite, actor);
                return;
            }
        }

        action_state = actor->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_state) {
        case 8:
            if ((try_turn_actor_toward_target(entity, context, sprite, actor) << 16) != 0) {
                return;
            }
            begin_actor_action(entity, context, sprite, actor);
            return;

        case 9:
            if (entity->unk_B4.bytes[1] == 0) {
                complete_actor_action(entity, context, sprite, actor);
                return;
            }
            begin_actor_exclusive_action(entity, context, sprite, 1, 0);
            return;

        case 10:
            if (entity->unk_B4.bytes[1] == 0) {
                reset_action_and_decrement_actor_count(entity, context, sprite, actor);
                return;
            }
            begin_actor_exclusive_action(entity, context, sprite, 1, 0);
            return;

        case 12:
            update_actor_status_and_mp(actor);
            return;

        case 5:
        case 6:
        case 7:
            if (entity->unk_B4.bytes[1] == 0) {
                ActorRecord *player;
                s16 facing;

                facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                actor->facing = facing;
                if (player->action_id != 0x11) {
                    update_actor_status_and_mp(actor);
                    return;
                }
                if (entity->unk_B4.bytes[1] == 0) {
                    prepare_actor_directional_action(entity, context, sprite, D_800E2418, uboat_behavior_entry);
                    return;
                }
            }
            {
                ActorRecord *leader = dungeon_actor_ring_anchor;

                if (leader->unk_A4.halves.high.u != 0) {
                    choose_and_execute_actor_step(entity, context, sprite, actor);
                    return;
                }
                leader->unk_A4.halves.high.u = 2;
                begin_actor_exclusive_action(entity, context, sprite, 1, 2);
                return;
            }

        case 2:
        case 1:
        case 3:
            if (entity->unk_B4.bytes[1] == 0) {
                begin_actor_spell_action(entity, context, sprite, D_800E2418, uboat_behavior_entry);
                return;
            } else {
                s32 action_mode = 1;

                begin_actor_exclusive_action(entity, context, sprite,
                    1, action_mode);
                return;
            }

        case 11:
        default:
            choose_and_execute_actor_step(entity, context, sprite, actor);
            return;
        }
    }

    if (!(((u32)actor->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }
}
