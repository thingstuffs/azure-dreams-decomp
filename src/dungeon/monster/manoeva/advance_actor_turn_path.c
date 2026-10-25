#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/monster/manoeva.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/actor_status.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "dungeon/level/room_flags.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 func_80171E38(void *, void *, void *, void *);
extern void update_actor_status_and_mp(void *);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void *find_adjacent_actor(void *, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 generate_random_value(void);
extern void *probe_directional_neighbor(void *, u8, u8, s16);
extern s16 get_actor_height_difference(void *, void *);
extern s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 test_neighbor_position_relation(s32, s32, s32, s32);
extern void select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern s16 check_movement_clearance_and_height(s16, void *, void *, s32);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s16 check_entity_relation(void *, void *);
extern s16 sample_terrain_surface_height(s32, s32, s16);

extern s16 actor_turn_angle_offsets[];

/* Selects and applies an actor movement step, updating its path and remaining movement. */
void advance_actor_turn_path(Rec_func_800A9E70_arg0 *move_data_in, void *context, SpriteFrameState *tile_in, ActorRecord *actor_in)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 stop_on_wide_turn = 0;
    s16 stop_turn;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_or_height;
    s16 *turn_table;
    s32 direction_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_in->movement_queue_state >= 0) {
        if (actor_in->unk_12 >= 2 ||
            (s16)func_80171E38(move_data_in, context, tile_in, actor_in) == 0) {
            update_actor_status_and_mp(actor_in);
            return;
        }
        if (g_dungeon_status.active_actor == actor_in) {
            actor_in->action_flags = 0xC008;
        }
        return;
    }

    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(tile_in, actor_in, 2, 4, &move_data_in->unk_9C.as_s8);
    actor_flags = actor_in->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_in, tile_in->tile_x,
                                  tile_in->tile_y);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = get_rounded_facing_and_rounding_flag(
                    tile_in->tile_x, tile_in->tile_y,
                    blocker_sprite->tile_x,
                    blocker_sprite->tile_y,
                    &move_data_in->unk_98);
                actor_in->facing = target_angle;
                actor_in->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_in->flags14 & 0x80000000)) {
                actor_in->flags14 |= 0x80000000;
                actor_in->facing +=
                    (generate_random_value() & 7) << 9;
            }
        } else if (probe_directional_neighbor(actor_in, tile_in->tile_x,
                          tile_in->tile_y,
                          actor_in->facing) != 0) {
            actor_in->movement_queue_state &= 0x7F;
            return;
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_in->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_data;
                {
                    TileObject *origin = &reference_tile_object;
                    s32 direction = ((u16)primary_actor_record->facing);
                    s32 table_index =
                        ((((u8 *)&actor_in->unk_44)[1] + ((s16)direction >> 9)) & 7) << 1;
                    target_x = origin->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + table_index);
                    target_y = origin->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + table_index);
                }

                if (tile_in->tile_x == (u16)target_x &&
                    tile_in->tile_y == (u16)target_y) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = &move_data_in->unk_98;
                target_angle = get_rounded_facing_and_rounding_flag(
                    tile_in->tile_x, tile_in->tile_y,
                    (s16)target_x, (s16)target_y, turn_data);
                actor_in->facing = target_angle;
                if (check_movement_clearance_and_height(target_angle, tile_in, actor_in, 0x20) <= 0) {
                    actor_in->facing = get_rounded_facing_and_rounding_flag(
                        tile_in->tile_x, tile_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, turn_data);
                }
                if (test_neighbor_position_relation(
                        tile_in->tile_x, tile_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    stop_on_wide_turn = 1;
                }
            } else {
                select_actor_route_target((u8 *)tile_in, move_data_in->unk_9C.as_s8, (u8 *)actor_in,
                              &move_data_in->unk_98);
            }
        }
    } else {
        if ((s8)tile_in->room_index >= 0 &&
            (dungeon_rooms[(s8)tile_in->room_index].flags & ROOM_HOLY_BEAM)) {
            select_actor_route_target((u8 *)tile_in, move_data_in->unk_9C.as_s8, (u8 *)actor_in,
                          &move_data_in->unk_98);
        } else if (!(actor_in->action_flags & ACTOR_ACTION_PENDING)) {
            current_angle = (s32)probe_directional_neighbor(actor_in, tile_in->tile_x,
                                  tile_in->tile_y,
                                  actor_in->facing);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0 &&
                (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
                (s16)get_actor_height_difference(blocker, actor_in) < 0x81) {
                if (check_diagonal_side_height(
                        (actor_in->facing >> 9) & 0xFFFF,
                        tile_in->tile_x, tile_in->tile_y,
                        (s16)(actor_in->ground_height - 0x20)) != 0) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }
            }

            if (actor_in->flags1C & ACTOR_PLAYER_AWARE) {
                TileObject *origin = &reference_tile_object;
                actor_in->facing = get_rounded_facing_and_rounding_flag(
                    tile_in->tile_x, tile_in->tile_y,
                    origin->tile_position.parts.tile_x, origin->tile_position.parts.tile_y, &move_data_in->unk_98);
                if (test_neighbor_position_relation(
                        tile_in->tile_x, tile_in->tile_y,
                        origin->tile_position.parts.tile_x, origin->tile_position.parts.tile_y) != 0) {
                    if (check_diagonal_side_height(
                            (actor_in->facing >> 9) & 0xFFFF,
                            tile_in->tile_x, tile_in->tile_y,
                            (s16)(actor_in->ground_height - 0x20)) != 0) {
                        actor_in->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            } else {
                select_actor_route_target((u8 *)tile_in, move_data_in->unk_9C.as_s8, (u8 *)actor_in,
                              &move_data_in->unk_98);
            }
        }
    }

    turn_or_height = -1;

    while (++turn_or_height < 8) {
        turn_flags = move_data_in->unk_98;
        current_angle = actor_in->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - actor_turn_angle_offsets[turn_or_height];
        } else {
            trial_angle = current_angle + actor_turn_angle_offsets[turn_or_height];
        }

        if (check_movement_clearance_and_height(trial_angle, tile_in, actor_in, 0x20) > 0) {
            if (turn_or_height >= 3) {
                stop_turn = stop_on_wide_turn;
                if (stop_turn != 0) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_in->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_in + (actor_in->movement_queue_state & 0x7F)))->path_x =
                tile_in->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_in + (actor_in->movement_queue_state & 0x7F)))->path_y =
                tile_in->tile_y;
            actor_in->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                tile_in->tile_x, tile_in->tile_y,
                (actor_in->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                direction_offset = ((u16)actor_in->facing >> 8) & 0xE;
                x_step += direction_offset;
                tile_in->tile_x += *x_step;
                tile_in->tile_y += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            }

            cycle_map_cell_flags(
                tile_in->tile_x, tile_in->tile_y,
                (actor_in->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_or_height == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&tile_in->tile_x) {
            if (check_entity_relation(actor_in,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_or_height >= 8) {
        actor_in->movement_queue_state &= 0x7F;
        actor_in->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_in);
        return;
    }

    {
        actor_in->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data_in->unk_9C.as_u8 = tile_in->room_index;
        actor_in->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_in->pending_turn_updates == 0) {
        actor_in->movement_queue_state &= 0x7F;
        return;
    }

    turn_or_height = sample_terrain_surface_height(
        (tile_in->tile_x << 6) | 0x20,
        (tile_in->tile_y << 6) | 0x20,
        (s16)(actor_in->ground_height - 0x20));
    if (turn_or_height < 0x200) {
        actor_in->ground_height = turn_or_height;
    }
}
