#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne_frames.h"


extern void select_sprite_entry(void *, u8, s32);
extern s8 find_active_rect_containing_point(u8, u8);
extern void update_actor_status_and_mp(ActorRecord *entity);

extern void update_directional_sprite_state_and_signals(void *, void *, void *, void *);

#include "dungeon/monster/hikewne.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

/* Updates actor behavior, animation, and facing from its status and current tile. */
void update_actor_behavior_animation_and_facing(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg) {
    register void *actor_head = actor_arg;
    register void *context = context_arg;
    register SpriteFrameState *sprite= sprite_arg;
    register ActorRecord *stats = stats_arg;
    s16 distance;
    s32 flags;
    s32 action_index;
    s8 tile_index;
    s16 angle;
    u16 action_flags;
    void *callback;
    ActorRecord *owner;
    void *actor_tail;
#define actor_arg actor_head
#define context_arg context

    if (g_dungeon_status.flags & 0x1000) {
        ((ActorRecord *)actor_arg)->action_id.u = 14;
        advance_actor_along_queued_path(actor_arg, context_arg, sprite, stats);
        return;
    }

    if (stats->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor_arg, context_arg, sprite, stats);
        if (*(u8 **)&sprite->frameTable == hikewne_frame_set_2) {
            return;
        }
        (sprite->frameTable) = hikewne_frame_set_1;
        select_sprite_entry(
            sprite,
            hikewne_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)stats->flags1C) & ACTOR_ASLEEP) {
        if (*(u8 **)&sprite->frameTable == hikewne_frame_set_2) {
            ((ActorRecord *)actor_arg)->action_id.u = 13;
            ((ActorRecord *)actor_arg)->action_phase.u = 1;
            ((ActorRecord *)actor_arg)->unk_8C.word = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite, hikewne_frame_set) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((u32)stats->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite, stats);
            return;
        }

        if (((ActorRecord *)actor_arg)->action_id.u != 14) {
            ((ActorRecord *)actor_arg)->action_id.u = 14;
        }

        if ((*(u8 **)&sprite->frameTable != hikewne_direction_frames) &&
            (*(u8 **)&sprite->frameTable != hikewne_alt_direction_frames)) {
            (sprite->frameTable) = hikewne_direction_frames;
            select_sprite_entry(
                sprite,
                hikewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            sprite->frame_ticks = 1;
            ((ActorRecord *)actor_arg)->unk_A0.halves.high.s = 0;
            ((ActorRecord *)actor_arg)->unk_9E.s = 0;
        }

        stats->flags1C |= 0x40000;
        ((ActorRecord *)actor_arg)->action_state_flags &= 0xFFF7;

        if (stats->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite, hikewne_frame_set_18) != 0) {
                return;
            }
        }

        if (((u32)stats->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite, stats);
            ((ActorRecord *)actor_arg)->unk_90.parts.high.u -= ((ActorRecord *)actor_arg)->unk_A0.parts.high;
            ((ActorRecord *)actor_arg)->unk_A0.halves.high.s = 0;
            ((ActorRecord *)actor_arg)->unk_9E.s = 0;
            update_directional_sprite_state_and_signals(actor_arg, context_arg, sprite, stats);
            return;
        }

        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor_arg, context_arg, sprite, stats);
        }
    }

    actor_tail = actor_head;
#undef actor_arg
#define actor_arg actor_tail
    tile_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_index;

    if (stats->pending_turn_updates > 0) {
        if (((u32)stats->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(stats);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
            return;
        }
        action_flags = stats->action_flags;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(
                            stats, previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)update_entity_state_from_query(actor_arg, context_arg, sprite, 0) == 0) {
                return;
            }
            action_flags = stats->action_flags | 0x4000;
            stats->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
                return;
            }
        }

        action_index = (stats->action_flags & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
        case 9:
            if ((s16)validate_action_and_apply_effect(actor_arg, context_arg, sprite, stats) != 0) {
                return;
            }
            clear_entity_flag_and_advance_action(actor_arg, context_arg, sprite, stats);
            return;

        case 4:
        case 5:
        case 6:
            angle = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            owner = primary_actor_record;
            stats->facing = angle;
            if (owner->action_id.u == 0x11) {
                callback = (void *)update_actor_behavior_animation_and_facing;
                begin_actor_spell_action(actor_arg, context_arg, sprite, 0, callback);
                return;
            }

        case 11:
            update_actor_status_and_mp(stats);
            return;

        case 0:
        case 1:
        case 2:
            callback = (void *)update_actor_behavior_animation_and_facing;

            begin_actor_spell_action(actor_arg, context_arg, sprite, 0, callback);
            return;

        default:
            select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
            return;
        }
    }

    flags = ((u32)stats->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (dungeon_rooms[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {

        if ((s16)test_neighbor_position_relation(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) == 0) {
            return;
        }
        stats->facing = get_rounded_facing_and_rounding_flag(
            sprite->tile_x, sprite->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
    }
#undef actor_arg
#undef context_arg
}
