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

extern s32 func_80171DFC(void *, void *, void *, void *);
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

/* Updates an actor's movement path, trying alternate directions around obstacles. */
void update_path_with_alternate_directions(ActorRecord *move_ctx_in, ObjectPosition *action_ctx, SpriteFrameState *position_in, ActorRecord *actor_in) {
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 near_target = 0;
    register s16 stop_turning;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 direction_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_in->movement_queue_state >= 0) {
        if (actor_in->unk_12 >= 2 ||
            (s16)func_80171DFC(move_ctx_in, action_ctx, position_in, actor_in) == 0) {
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

    update_actor_proximity_flag(position_in, actor_in, 3, 6, &move_ctx_in->unk_9C);
    actor_flags = actor_in->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_in, position_in->tile_x,
                                  position_in->tile_y);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = get_rounded_facing_and_rounding_flag(
                    position_in->tile_x, position_in->tile_y,
                    blocker_sprite->tile_x,
                    blocker_sprite->tile_y,
                    &move_ctx_in->action_state_flags);
                actor_in->facing = target_angle;
                actor_in->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_in->flags14 & 0x80000000)) {
                actor_in->flags14 |= 0x80000000;
                actor_in->facing +=
                    (generate_random_value() & 7) << 9;
            }
        } else if (probe_directional_neighbor(actor_in, position_in->tile_x,
                          position_in->tile_y,
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
                u16 *move_flags;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_heading = ((u16)primary_actor_record->facing);
                    s32 table_index =
                        ((((u8 *)&actor_in->unk_44)[1] + ((s16)target_heading >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + table_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + table_index);
                }

                if (position_in->tile_x == (u16)target_x &&
                    position_in->tile_y == (u16)target_y) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }

                move_flags = &move_ctx_in->action_state_flags;
                target_angle = get_rounded_facing_and_rounding_flag(
                    position_in->tile_x, position_in->tile_y,
                    (s16)target_x, (s16)target_y, move_flags);
                actor_in->facing = target_angle;
                if (check_movement_clearance_and_height(target_angle, position_in, actor_in, 0x20) <= 0) {
                    actor_in->facing = get_rounded_facing_and_rounding_flag(
                        position_in->tile_x, position_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, move_flags);
                }
                if (test_neighbor_position_relation(
                        position_in->tile_x, position_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    near_target = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_in, move_ctx_in->unk_9C, (u8 *)actor_in,
                              &move_ctx_in->action_state_flags);
            }
        }
    } else {
        if ((s8)position_in->room_index >= 0 &&
            (dungeon_rooms[(s8)position_in->room_index].flags & ROOM_HOLY_BEAM)) {
            select_actor_route_target((u8 *)position_in, move_ctx_in->unk_9C, (u8 *)actor_in,
                          &move_ctx_in->action_state_flags);
        } else if (!(actor_in->action_flags & ACTOR_ACTION_PENDING) &&
                   !(move_ctx_in->action_state_flags & 0x8000)) {
            current_angle = (s32)probe_directional_neighbor(actor_in, position_in->tile_x,
                                  position_in->tile_y,
                                  actor_in->facing);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0 &&
                (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
                (s16)get_actor_height_difference(blocker, actor_in) < 0x81) {
                if (check_diagonal_side_height(
                        (actor_in->facing >> 9) & 0xFFFF,
                        position_in->tile_x, position_in->tile_y,
                        (s16)(actor_in->ground_height - 0x20)) != 0) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }
            }

            if (actor_in->flags1C & ACTOR_PLAYER_AWARE) {
                TileObject *target_position = &reference_tile_object;
                actor_in->facing = get_rounded_facing_and_rounding_flag(
                    position_in->tile_x, position_in->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, &move_ctx_in->action_state_flags);
                if (test_neighbor_position_relation(
                        position_in->tile_x, position_in->tile_y,
                        target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                    if ((s16)get_actor_height_difference(primary_actor_record, actor_in) < 0x81) {
                        if (check_diagonal_side_height(
                                (actor_in->facing >> 9) & 0xFFFF,
                                position_in->tile_x,
                                    position_in->tile_y,
                                (s16)(actor_in->ground_height - 0x20)) != 0) {
                            actor_in->movement_queue_state &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                select_actor_route_target((u8 *)position_in, move_ctx_in->unk_9C, (u8 *)actor_in,
                              &move_ctx_in->action_state_flags);
            }
        }
    }

    turn_index = -1;

    while (++turn_index < 8) {
        turn_flags = move_ctx_in->action_state_flags;
        current_angle = actor_in->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - actor_turn_angle_offsets[turn_index];
        } else {
            trial_angle = current_angle + actor_turn_angle_offsets[turn_index];
        }

        if (check_movement_clearance_and_height(trial_angle, position_in, actor_in, 0x20) > 0) {
            if (turn_index >= 3) {
                stop_turning = near_target;
                if (stop_turning != 0) {
                    actor_in->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_in->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_in + (actor_in->movement_queue_state & 0x7F)))->path_x =
                position_in->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_in + (actor_in->movement_queue_state & 0x7F)))->path_y =
                position_in->tile_y;
            actor_in->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_in->tile_x, position_in->tile_y,
                (actor_in->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                direction_offset = ((u16)actor_in->facing >> 8) & 0xE;
                x_step += direction_offset;
                position_in->tile_x += *x_step;
                position_in->tile_y += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            }

            cycle_map_cell_flags(
                position_in->tile_x, position_in->tile_y,
                (actor_in->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&position_in->tile_x) {
            if (check_entity_relation(actor_in,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        actor_in->movement_queue_state &= 0x7F;
        actor_in->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_in);
        return;
    }

    {
        actor_in->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_ctx_in->unk_9C = position_in->room_index;
        actor_in->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_in->pending_turn_updates == 0) {
        actor_in->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (position_in->tile_x << 6) | 0x20,
        (position_in->tile_y << 6) | 0x20,
        (s16)(actor_in->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_in->ground_height = turn_index;
    }
}
