#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/actor_status.h"
#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "dungeon/level/room_flags.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/monster/hikewne.h"

s32 validate_action_and_apply_effect(ActorRecord *action, ObjectPosition *effect, SpriteFrameState *target, ActorRecord *actor_data);
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
extern s16 check_directional_move_and_terrain(s16, void *, void *, s32);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s16 check_entity_relation(void *, void *);
extern s16 sample_terrain_surface_height(s32, s32, s16);

extern s16 actor_turn_angle_offsets[];

/* Selects a movement direction and updates the actor's position and movement state. */
void select_movement_direction_and_advance(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data) {
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (actor_data->unk_12 >= 2 ||
            (s16)validate_action_and_apply_effect(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data, position_data->tile_x, position_data->tile_y);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = get_rounded_facing_and_rounding_flag(
                    position_data->tile_x, position_data->tile_y,
                    blocker_sprite->tile_x, blocker_sprite->tile_y,
                    &move_data->action_state_flags);
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing += (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data, position_data->tile_x, position_data->tile_y, actor_data->facing) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_x == (u16)target_x &&
                    position_data->tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = &move_data->action_state_flags;
                target_angle = get_rounded_facing_and_rounding_flag(
                    position_data->tile_x, position_data->tile_y,
                    (s16)target_x, (s16)target_y, turn_data);
                actor_data->facing = target_angle;
                if (check_directional_move_and_terrain(target_angle, position_data, actor_data, 0x20) <= 0) {
                    actor_data->facing = get_rounded_facing_and_rounding_flag(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, turn_data);
                }
                if (test_neighbor_position_relation(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                              &move_data->action_state_flags);
            }
        }
    } else if ((s8)position_data->room_index >= 0 &&
               dungeon_rooms[(s8)position_data->room_index].flags & ROOM_HOLY_BEAM) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                      &move_data->action_state_flags);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data, position_data->tile_x, position_data->tile_y, actor_data->facing);
        blocker = (ActorRecord *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)get_actor_height_difference(blocker, actor_data) < 0x81) {
            if (check_diagonal_side_height(
                    (actor_data->facing >> 9) & 0xFFFF,
                    position_data->tile_x, position_data->tile_y,
                    (s16)(actor_data->ground_height - 0x20)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = get_rounded_facing_and_rounding_flag(
                position_data->tile_x, position_data->tile_y,
                target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, &move_data->action_state_flags);
            if (test_neighbor_position_relation(
                    position_data->tile_x, position_data->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                if (get_actor_height_difference(primary_actor_record, actor_data) < 0x81) {
                    if (check_diagonal_side_height(
                            (actor_data->facing >> 9) & 0xFFFF,
                            position_data->tile_x,
                                position_data->tile_y,
                            (s16)(actor_data->ground_height - 0x20)) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                          &move_data->action_state_flags);
        }
    }

    turn_index = 0;
    turn_table = actor_turn_angle_offsets;

    for (; turn_index < 8; turn_index++) {
        turn_flags = move_data->action_state_flags;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (check_directional_move_and_terrain(trial_angle, position_data, actor_data, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            /* remember the cell in the actor's trail of visited cells */
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_x =
                position_data->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_y =
                position_data->tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_x, position_data->tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = ((u16)actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_x += *x_step;
                position_data->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags(
                position_data->tile_x, position_data->tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&position_data->tile_x) {
            if (check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                return;
            }
        }
    }

    if (turn_index >= 8) {
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (position_data->tile_x << 6) | 0x20,
        (position_data->tile_y << 6) | 0x20,
        (s16)(actor_data->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}
