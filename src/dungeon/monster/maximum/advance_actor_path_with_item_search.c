#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/actor_status.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "dungeon/level/room_flags.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/item.h"
extern int abs(int);

extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 check_diagonal_side_height(s32, u8, u8, s16);
extern s16 check_movement_clearance_and_height(s16, void *, void *, s32);
extern s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 generate_random_value(void);
extern s16 find_nearest_floor_item_in_room(void *, s32, s16 *, s16 *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 sample_terrain_surface_height(s32, s32, s16);
extern s32 func_80171EBC(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor);

extern s8 actor_turn_angle_offsets;

/*
 * Steers Maximum toward nearby floor items or its movement target, tries clear headings, and
 * records the path and occupancy.
 */
void advance_actor_path_with_item_search(ActorRecord *move_state, ObjectPosition *caller_context, SpriteFrameState *position_arg, ActorRecord *actor_arg) {
    s16 target_x;
    s16 target_y;
    s16 turn_index;
    s32 next_angle;
    s32 limit_turns;
    s32 flags;
    s32 follow_x;
    s32 follow_y;
    s32 target_x_wide;
    s32 dx;
    s32 dy;
    u32 table_offset;
    void *angle;
    DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
    u16 *angle_context;
    u16 *follow_context;
    s16 *turn_table;

    limit_turns = 0;
    flags = dungeon_state->flags;
    if ((flags & 0x4000) || ((s8)actor_arg->movement_queue_state >= 0)) {
        if ((actor_arg->unk_12 >= 2) ||
            ((s16)func_80171EBC(move_state, caller_context, position_arg, actor_arg) == 0)) {
            update_actor_status_and_mp(actor_arg);
            return;
        }
        if (dungeon_state->active_actor == actor_arg) {
            actor_arg->action_flags = 0xC008;
        }
        return;
    }

    if (!(flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_arg, actor_arg, 3, 6, &move_state->unk_9C);
    flags = actor_arg->flags1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            angle = find_adjacent_actor(actor_arg, position_arg->tile_x,
                                  position_arg->tile_y);
            if (angle != 0) {
                SpriteFrameState *other = ((ObjectNodeHeader *)angle - 1)->sprite;

                actor_arg->facing = get_rounded_facing_and_rounding_flag(
                    position_arg->tile_x, position_arg->tile_y,
                    other->tile_x, other->tile_y,
                    &move_state->action_state_flags);
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }
            {
                s32 sign_mask = 0x80000000;
                s32 state_flags;

                state_flags = actor_arg->flags14;
                if (state_flags >= 0) {
                    state_flags |= sign_mask;
                    actor_arg->flags14 = state_flags;
                    sign_mask = generate_random_value();
                    actor_arg->facing += (sign_mask & 7) << 9;
                }
            }
        } else {
            angle = probe_directional_neighbor(actor_arg, position_arg->tile_x,
                                  position_arg->tile_y,
                                  actor_arg->facing);
            if (angle != 0) {
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (flags & 0x2000) {
        turn_index = 0;
        if (!(actor_arg->action_flags & ACTOR_ACTION_PENDING)) {
            if (!(flags & 0x20000)) {
                select_actor_route_target((u8 *)position_arg, move_state->unk_9C, (u8 *)actor_arg,
                              &move_state->action_state_flags);
            } else {
                {
                    u32 follow_offset;

                    follow_offset =
                        ((((u8 *)&actor_arg->unk_44)[1] +
                          ((s32)(((u16)primary_actor_record->facing) << 16) >> 25)) &
                         7) *
                        2;

                    follow_x = reference_tile_object.tile_position.parts.tile_x + *(u16 *)((u8 *)((s8 *)dir_step_x) + follow_offset);
                    follow_y = reference_tile_object.tile_position.parts.tile_y + *(u16 *)((u8 *)((s8 *)dir_step_y) + follow_offset);
                }
                target_x = follow_x;
                target_y = follow_y;

                if ((position_arg->tile_x == (u16)follow_x) &&
                    (position_arg->tile_y == (u16)follow_y)) {
                    actor_arg->movement_queue_state &= 0x7F;
                    return;
                }

                actor_arg->facing = get_rounded_facing_and_rounding_flag(
                    position_arg->tile_x, position_arg->tile_y, target_x,
                        target_y,
                    angle_context = &move_state->action_state_flags);
                if (check_movement_clearance_and_height(actor_arg->facing, position_arg, actor_arg, 0x20) <=
                    0) {
                    actor_arg->facing = get_rounded_facing_and_rounding_flag(
                        position_arg->tile_x, position_arg->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        angle_context);
                }
                {
                    s16 path_ok = test_neighbor_position_relation(position_arg->tile_x,
                                                position_arg->tile_y,
                                                reference_tile_object.tile_position.parts.tile_x,
                                                reference_tile_object.tile_position.parts.tile_y);

                    if (path_ok != 0) {
                        limit_turns = 1;
                    }
                }
                turn_index = 0;
            }
        }
    } else {
        turn_index = find_nearest_floor_item_in_room(position_arg, 0x12, &target_x, &target_y);
        if ((s8)position_arg->room_index >= 0) {
            s32 room = (s8)position_arg->room_index;

            if (dungeon_rooms[room].flags & ROOM_HOLY_BEAM) {
                goto call_obstacle;
            }
        }

        if (!(actor_arg->action_flags & ACTOR_ACTION_PENDING)) {
            angle = probe_directional_neighbor(actor_arg, position_arg->tile_x,
                                  position_arg->tile_y, actor_arg->facing);
            if ((angle != 0) && (((ActorRecord *)angle)->flags1C & ACTOR_PLAYER_SIDE) &&
                (get_actor_height_difference(angle, actor_arg) < 0x81) &&
                ((s16)check_diagonal_side_height(
                     (actor_arg->facing >> 9) & 0xFFFF,
                     position_arg->tile_x, position_arg->tile_y,
                     (s16)(actor_arg->ground_height - 0x20)) != 0)) {
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }

            if (actor_arg->flags1C & ACTOR_PLAYER_AWARE) {
                follow_context = &move_state->action_state_flags;
                actor_arg->facing = get_rounded_facing_and_rounding_flag(
                    position_arg->tile_x, position_arg->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    follow_context);
                if ((s16)test_neighbor_position_relation(position_arg->tile_x,
                                       position_arg->tile_y,
                                       reference_tile_object.tile_position.parts.tile_x,
                                       reference_tile_object.tile_position.parts.tile_y) != 0) {
                    if (get_actor_height_difference(primary_actor_record, actor_arg) < 0x81) {
                        if ((s16)check_diagonal_side_height(
                                (actor_arg->facing >> 9) & 0xFFFF,
                                position_arg->tile_x, position_arg->tile_y,
                                (s16)(actor_arg->ground_height - 0x20)) != 0) {
                            actor_arg->movement_queue_state &= 0x7F;
                            return;
                        }
                        if (turn_index != 0) {
                            dx = position_arg->tile_x;
                            dx -= (target_x_wide = (u16)target_x);
                            dx = abs(dx);
                            if (dx >= 2 || (dy = abs(position_arg->tile_y - (u16)target_y)) >= 2) {
                                actor_arg->facing = get_rounded_facing_and_rounding_flag(
                                    position_arg->tile_x, position_arg->tile_y,
                                        (s16)target_x_wide, target_y,
                                    follow_context);
                            } else {
                                actor_arg->facing = (generate_random_value() & 7) << 9;
                            }
                        }
                    }
                }
            } else {
                if (turn_index == 0) {
                    select_actor_route_target((u8 *)position_arg, move_state->unk_9C, (u8 *)actor_arg,
                  &move_state->action_state_flags);
                } else {
                    dx = position_arg->tile_x;
                    dx -= (target_x_wide = (u16)target_x);
                    dx = abs(dx);
                    if (dx >= 2 || (dy = abs(position_arg->tile_y - (u16)target_y)) >= 2) {
                        actor_arg->facing = get_rounded_facing_and_rounding_flag(
                            position_arg->tile_x, position_arg->tile_y,
                                (s16)target_x_wide, target_y,
                            &move_state->action_state_flags);
                    } else {
                        actor_arg->facing = (generate_random_value() & 7) << 9;
                    }
                }
            }
        }
    }
    goto loop_setup;
call_obstacle:
    select_actor_route_target((u8 *)position_arg, move_state->unk_9C, (u8 *)actor_arg,
                  &move_state->action_state_flags);

loop_setup:
    turn_index = 0;
    turn_table = (s16 *)&actor_turn_angle_offsets;

    for (; turn_index < 8; turn_index++) {
        {

            angle = (void *)(actor_arg->facing);
            if (move_state->action_state_flags & 2) {
                next_angle = ((s32)angle) - turn_table[turn_index];
            } else {
                next_angle = ((s32)angle) + turn_table[turn_index];
            }
        }

        if (check_movement_clearance_and_height((s16)next_angle, position_arg, actor_arg, 0x20) > 0) {
            if (turn_index >= 3) {
                s16 turn_limit;

                turn_limit = limit_turns;
                if (turn_limit != 0) {
                    actor_arg->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_arg->facing = next_angle;
            ((ActorStatusBytesView *)((u8 *)actor_arg + (actor_arg->movement_queue_state & 0x7F)))->path_x =
                position_arg->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_arg + (actor_arg->movement_queue_state & 0x7F)))->path_y =
                position_arg->tile_y;
            actor_arg->movement_queue_state++;

            update_map_cell_flags_with_item_limit(position_arg->tile_x, position_arg->tile_y,
                          (actor_arg->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            table_offset = (*(u16 *)&actor_arg->facing >> 8) & 0xE;
            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                x_step += table_offset;
                position_arg->tile_x += *x_step;
            }
            position_arg->tile_y +=
                *(u8 *)((u8 *)((s8 *)dir_step_y) + table_offset);

            cycle_map_cell_flags(position_arg->tile_x, position_arg->tile_y,
                          (actor_arg->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0) {
            if (reference_tile_object.tile_position.word != *(u16 *)&position_arg->tile_x) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(
                            actor_arg,
                            previous_actor) != 0) {
                        return;
                    }
                }
            }
        }

    }

    if (turn_index >= 8) {
        actor_arg->movement_queue_state &= 0x7F;
        actor_arg->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_arg);
        return;
    }

    actor_arg->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    move_state->unk_9C = position_arg->room_index;
    actor_arg->pending_turn_updates--;
    {
        DungeonGlobalStatus *counter_state = &g_dungeon_status;

        counter_state->activity_counts.parts.pending_movement_count++;
    }
    if (actor_arg->pending_turn_updates == 0) {
        actor_arg->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height((position_arg->tile_x << 6) | 0x20,
                               (position_arg->tile_y << 6) | 0x20,
                               (s16)(actor_arg->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_arg->ground_height = turn_index;
    }
    return;

    return;
}
