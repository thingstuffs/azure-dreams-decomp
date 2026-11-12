#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "engine/entity/effect_slots.h"
#include "dungeon/system/random.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/golem.h"
#include "engine/graphics.h"
#include "dungeon/actor/motion.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/state.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/golem_frames.h"




extern u8 golem_direction_frames[];
extern u8 golem_frame_set_2;
extern u8 golem_frame_set_3[];
extern u8 D_80175F50;
extern u8 D_80175F60;

#include "dungeon/item/find_active_rect_containing_point_api.h"
extern void advance_stored_path_motion();
extern void update_actor_movement_and_tile_position();
extern s32 func_801727D8(); /* Slot contract: loading images do not establish one callee contract. */
extern s32 func_80174698();

/* Update an actor's dungeon actions, status, facing, and animation. */
/* Dispatches Golem's movement, attacks, spells, and turn processing, creating a sprite copy for its
 * alternate mode. */
void update_dungeon_actor_actions(GolemActionWork *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats) {
    s16 heading_flags;
    s32 tile_index;
    u32 action_index;
    u32 state;
    u32 active_state;
    u32 idle_state;
    u8 *active_anims;
    u8 *next_anims;
    u8 *anim_entry;
    register void *anim_sprite;

    if ((actor->mode == 0) && (g_dungeon_status.flags & 0x1000)) {
        actor->state = 14;
        advance_stored_path_motion(actor, context, sprite, stats);
        return;
    }

    if (stats->mp_value.parts.whole == 0) {
        consume_pending_flag(actor, stats);
        advance_actor_pending_action(actor, context, sprite, stats);
        if (sprite->frameTable == golem_alt_direction_frames) {
            return;
        }
        sprite->frameTable = &golem_frame_set_2;
        select_sprite_entry(sprite,
            (&golem_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7], 0);
        return;
    }

    if ((u32)stats->flags1C & ACTOR_ASLEEP) {
        if (sprite->frameTable == golem_alt_direction_frames) {
            actor->state = 13;
            actor->phase = 1;
            actor->callback = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        consume_pending_flag(actor, stats);
        if (reset_actor_action_state(actor, context, sprite, &golem_frame_set_2)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((u32)stats->flags1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, stats);
            return;
        }

        state = actor->state;
        active_state = 25;
        idle_state = 14;
        if (state != active_state && actor->mode != 0) {
            u8 *active_table = golem_frame_set_3;
            if (sprite->frameTable != active_table) {
                create_copied_render_object(actor, context, sprite);
                sprite->frameTable = active_table;
                select_sprite_entry(sprite,
                    active_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->state = active_state;
        } else {
            state = actor->state;
            idle_state = 14;
            if (state != idle_state) {
                if (actor->mode == 0) {
                    u8 *idle_table = golem_direction_frames;
                    if (sprite->frameTable != idle_table) {
                        sprite->frameTable = idle_table;
                        select_sprite_entry(sprite,
                            idle_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                            0);
                    }
                    actor->state = idle_state;
                }
            }
        }

        actor->flags &= 0xFFF3;
        if (stats->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, &D_80175F50)) {
                return;
            }
        }
        if ((u32)stats->flags1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, stats);
            func_80174698(actor, context, sprite, stats);
            return;
        }
        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor, context, sprite, stats);
        }
    tile_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_index;
    } else {
    tile_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_index;
    }

    if (stats->pending_turn_updates > 0) {
        if ((u32)stats->flags1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(stats);
            return;
        }
        if ((*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) &&
            (actor->mode == 0)) {
            consume_pending_flag(actor, stats);
            update_actor_movement_and_tile_position(actor, context, sprite, stats);
            return;
        }

        if (!(stats->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(stats,
                        NODE_BODY(primary_actor_record->previous_actor_header)) != 0) {
                    return;
                }
            }
            if (actor->mode == 0) {
                if ((s16)func_801727D8(actor, context, sprite, 0) == 0) {
                    return;
                }
            }
            stats->action_flags |= 0x4000;
            if (!(stats->action_flags & 0x8000)) {
                update_actor_movement_and_tile_position(actor, context, sprite, stats);
                if (actor->mode != 0) {
                    consume_pending_flag(actor, stats);
                }
                return;
            }
        }

        action_index = (stats->action_flags & 0x3FFF) - 1;
        switch (action_index) {
        case 11:
            if (consume_pending_flag(actor, stats) == 0) {
                update_actor_status_and_mp(stats);
                return;
            }
            sprite->frameTable = golem_direction_frames;
            select_sprite_entry(sprite,
                golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7], 0);
            update_actor_status_and_mp(stats);
            return;

        case 10:
            update_actor_movement_and_tile_position(actor, context, sprite, stats);
            consume_pending_flag(actor, stats);
            return;

        case 7:
            consume_pending_flag(actor, stats);
            if ((s16)attempt_actor_action_and_display(actor, context, sprite, stats) != 0) {
                return;
            }
            update_eligible_actor_action(actor, context, sprite, stats);
            return;

        case 8:
            if (actor->mode != 0) {
                if (stats->flags1C & ACTOR_CONFUSED) {
                    s32 turn_flags = stats->flags14;
                    if ((turn_flags & 0x80000000) == 0) {
                        stats->flags14 = (u32)turn_flags | 0x80000000;
                        stats->facing +=
                            (generate_random_value() & 7) << 9;
                    }
                }
                scan_forward_tiles_for_target(actor, context, sprite, stats);
                return;
            }
            initialize_directional_animation_action(actor, context, sprite, stats);
            return;

        case 4:
        case 5:
        case 6:
        {
            s16 heading;
            ActorRecord *leader;

            heading = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &heading_flags);
            leader = primary_actor_record;
            stats->facing = heading;
            if (leader->action_id != 17) {
                update_actor_status_and_mp(stats);
                return;
            }
        }

        case 0:
        case 1:
        case 2:
            consume_pending_flag(actor, stats);
            begin_actor_spell_action(actor, context, sprite, &D_80175F60, update_dungeon_actor_actions);
            return;

        default:
            update_actor_movement_and_tile_position(actor, context, sprite, stats);
            if (actor->mode != 0) {
                consume_pending_flag(actor, stats);
            }
            return;
        }
    } else {
        if (actor->mode == 0) {
            u32 flags = (u32)stats->flags1C;
            if (!(flags & 0x2000)) {
                if (!((s8)tile_index >= 0 && (dungeon_rooms[(s8)tile_index].flags & 2)) && !(flags & 0x430)) {
                    if ((s16)test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                        stats->facing = get_rounded_facing_and_rounding_flag(
                            sprite->tile_x, sprite->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &heading_flags);
                    }
                }
            } else if ((s16)get_entity_effect_value(stats, STATUS_PARALYSIS) == 0) {
                if (primary_actor_record->action_id == 23) {
                    advance_timed_directional_reset(actor, context, sprite, stats);
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
    if (actor->mode != 0) {
        active_anims = golem_frame_set_3;
        if (sprite->frameTable == active_anims) {
            return;
        }
        create_copied_render_object(actor, context, sprite);
        sprite->frameTable = active_anims;
        anim_sprite = sprite;
        anim_entry = active_anims + (((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7);
    } else {
        void *current_anims;
        u8 *idle_anims;

        current_anims = sprite->frameTable;
        idle_anims = golem_direction_frames;
        if (current_anims == idle_anims) {
            return;
        }
        next_anims = idle_anims;

        sprite->frameTable = next_anims;
        anim_sprite = sprite;
        anim_entry = (u8 *)((unsigned long)
            (((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7) +
            (unsigned long)next_anims);
    }

    select_sprite_entry(anim_sprite, *anim_entry, 0);
}
