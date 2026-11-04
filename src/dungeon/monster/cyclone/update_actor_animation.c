#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/monster/nyuel.h"



extern void select_sprite_entry(void *, u8, s32);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);

extern void func_80174520(void *, void *, void *, void *);

extern u8 cyclone_move_direction_frames[];
extern u8 D_80176468[];
#include "dungeon/monster/cyclone.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

extern u8 D_801764A8[];

/* Updates actor animation, status, and behavior according to dungeon state. */
void update_actor_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg) {
    ActorRecord *stats = stats_arg;
    s16 distance;
    s8 tile_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor_arg->action_id.u = 14;
        advance_path_motion(actor_arg, context_arg, sprite_arg, stats);
        return;
    }

    if (stats->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor_arg, context_arg, sprite_arg, stats);
        if (*(u8 **)&sprite_arg->frameTable == cyclone_direction_frames) {
            return;
        }
        {
            u8 *animations = D_80176468;
            (sprite_arg->frameTable) = animations;
            select_sprite_entry(
                sprite_arg,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (stats->flags1C & 0x200) {
        if (*(u8 **)&sprite_arg->frameTable == cyclone_direction_frames) {
            actor_arg->action_id.u = 13;
            actor_arg->action_phase.u = 1;
            actor_arg->unk_8C.word = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite_arg, D_80176468) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (stats->flags1C & 0x100) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if (actor_arg->action_id.u != 14) {
            actor_arg->action_id.u = 14;
        }

        if (*(u8 **)&sprite_arg->frameTable != cyclone_move_direction_frames) {
            u8 *animations = cyclone_move_direction_frames;
            (sprite_arg->frameTable) = animations;
            select_sprite_entry(
                sprite_arg,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            sprite_arg->frame_ticks = 1;
            actor_arg->unk_A4.halves.high.s = 0;
            actor_arg->unk_AC.halves.low.s = 0;
        }

        {
            u32 flags = stats->flags1C;
            u16 actor_flags;

            if (flags & 0x20) {
                stats->flags1C = flags & ~0x40000;
                actor_flags = actor_arg->action_state_flags | 8;
            } else {
                stats->flags1C = flags | 0x40000;
                actor_flags = actor_arg->action_state_flags & 0xFFF7;
            }
            actor_arg->action_state_flags = actor_flags;
        }

        if (stats->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite_arg, D_801764A8) != 0) {
                return;
            }
        }

        if (stats->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite_arg, stats);
            actor_arg->unk_90.parts.high.u -= actor_arg->unk_A4.halves.high.u;
            actor_arg->unk_A4.halves.high.u = 0;
            actor_arg->unk_AC.halves.low.u = 0;
            func_80174520(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor_arg, context_arg, sprite_arg, stats);
        }
    }

    tile_id = find_active_rect_containing_point(sprite_arg->tile_x, sprite_arg->tile_y);
    sprite_arg->room_index = tile_id;

    if (stats->pending_turn_updates > 0) {
        if (stats->flags1C & 0x20) {
            update_actor_status_and_mp(stats);
            return;
        }
        if (*(u16 *)&sprite_arg->tile_x == reference_tile_object.tile_position.word) {
            update_actor_movement_and_tile_position(actor_arg, context_arg, sprite_arg, stats);
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
            if ((s16)update_entity_state_from_query(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_flags = stats->action_flags | 0x4000;
            stats->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                update_actor_movement_and_tile_position(actor_arg, context_arg, sprite_arg, stats);
            return;
            }
        }

        switch (stats->action_flags & 0x3FFF) {
        case 8:
            if ((s16)check_movement_and_initialize_action(actor_arg, context_arg, sprite_arg, stats) != 0) {
                return;
            }
            finish_actor_tile_move_and_check_trap(actor_arg, context_arg, sprite_arg, stats);
            return;
        case 9:
            if (stats->flags1C & 0x400) {
                s32 behavior_state;
                behavior_state = stats->flags14;
                if ((behavior_state & 0x80000000) == 0) {
                    behavior_state |= 0x80000000;
                    stats->flags14 = behavior_state;
                    stats->facing += (generate_random_value() & 7) << 9;
                }
            }
            switch ((s16)search_ahead_and_start_action(actor_arg, context_arg, sprite_arg, stats)) {
            case -1:
            case 1:
                break;
            case 0:
                update_action_state_direction_specific(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 2:
                clear_actor_action_flag_and_animate(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 3:
                attempt_actor_directional_action(actor_arg, context_arg, sprite_arg, stats);
                return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                s16 heading = get_rounded_facing_and_rounding_flag(
                    sprite_arg->tile_x, sprite_arg->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                ActorRecord *player = primary_actor_record;
                stats->facing = heading;
                if (player->action_id.u == 0x11) {
                    begin_actor_spell_action(actor_arg, context_arg, sprite_arg, cyclone_move_direction_frames, update_actor_animation);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(stats);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, sprite_arg, cyclone_move_direction_frames, update_actor_animation);
            return;
        default:
            update_actor_movement_and_tile_position(actor_arg, context_arg, sprite_arg, stats);
            return;
        }
    }

    {
        u32 flags = stats->flags1C;

        if (!(flags & 0x2000)) {
            s32 tile_index = (s8)tile_id;

            if ((tile_index < 0) ||
                !(dungeon_rooms[tile_index].flags & 2)) {
                if (!(flags & 0x430)) {
                    if ((s16)test_neighbor_position_relation(
                            sprite_arg->tile_x, sprite_arg->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                        stats->facing = get_rounded_facing_and_rounding_flag(
                            sprite_arg->tile_x, sprite_arg->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                            &distance);
                    }
                }
            }
        }
    }
}
