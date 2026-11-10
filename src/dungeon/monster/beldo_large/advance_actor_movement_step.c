#include "common.h"
#include "dungeon/system/random.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "dungeon/level/room_flags.h"
#include "dungeon/item.h"
#include "dungeon/item/actor_target.h"

#ifndef NULL
#define NULL 0
#endif



struct ActorRecord; 
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/item/state.h"
#include "dungeon/level.h"

s32 check_diagonal_side_height(s32, s16, s16, s16);
extern s32 check_movement_clearance_and_height();
#include "dungeon/item/get_actor_height_difference_api.h"
#include "dungeon/actor/state.h"

struct Rec_D_80082E80; struct Rec_func_800A9E70_arg0;

extern s16 actor_turn_angle_offsets[];

/* Select a movement direction, record the previous tile, and update the actor position and height. */
/* Chooses Beldo's next clear step from actor or player-relative targets, records the path, and updates
 * tile occupancy and height. */
void advance_actor_movement_step(ActorRecord *movement_in, ObjectPosition *action_ctx, SpriteFrameState *position, ActorRecord *actor) {
    u16 near_target;
    u8 target_nearby = 0;
    s16 height_result;
    s32 attempt;
    register u8 *x_offsets;
    DungeonGlobalStatus *dungeon_state;
    DungeonGlobalStatus *turn_state;
    u32 dungeon_flags;
    u32 actor_flags;
    s32 path_result;
    s32 random_bits;
    s32 direction_offset;
    s32 moved;
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    s32 next_y;
    ActorRecord *found;
    SpriteFrameState *object;

    dungeon_state = &g_dungeon_status;
    dungeon_flags = dungeon_state->flags;
    near_target = 0;

    if ((dungeon_flags & 0x4000) || ((s8)actor->movement_queue_state >= 0)) {
        if ((actor->unk_12 >= 2) ||
            ((try_actor_attack(movement_in, action_ctx, position, actor) << 16) == 0)) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (dungeon_state->active_actor != actor) {
            return;
        }
        actor->action_flags = 0xC008;
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, &movement_in->unk_9C);
    actor_flags = actor->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found = find_adjacent_actor(actor, position->tile_x,
                position->tile_y);
            if (found != NULL) {
                object = NODE_HEADER(found)->sprite;
                actor->facing = get_rounded_facing_and_rounding_flag(
                    position->tile_x, position->tile_y,
                    object->tile_x, object->tile_y, &movement_in->action_state_flags);
                actor->movement_queue_state &= 0x7F;
                return;
            }
            {
                s32 object_status;

                object_status = actor->flags14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    actor->flags14 = object_status;
                    random_bits = generate_random_value();
                    actor->facing += (random_bits & 7) << 9;
                }
            }
        } else {
            found = probe_directional_neighbor(actor, position->tile_x,
                position->tile_y,
                                  actor->facing);
            if (found != NULL) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (movement_in->unk_AC.bytes[3]) {
        if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s32 direction;
                s16 target_x;
                s32 target_y;
                s16 new_angle;
                TileObject *target;

                target = &reference_tile_object;
                direction = (((u8 *)&actor->unk_44.whole)[1] +
                             ((s32)(((u16)primary_actor_record->facing) << 16) >> 25)) & 7;
                target_x = target->tile_position.parts.tile_x +
                           (u16)dir_step_x[direction];
                target_y = target->tile_position.parts.tile_y +
                           (u16)dir_step_y[direction];
                if ((position->tile_x == (u16)target_x) &&
                    (position->tile_y == (u16)target_y)) {
                    actor->movement_queue_state &= 0x7F;
                    return;
                }
                new_angle = get_rounded_facing_and_rounding_flag(position->tile_x,
                    position->tile_y,
                                          target_x, (s16)target_y, &movement_in->action_state_flags);
                actor->facing = new_angle;
                if ((check_movement_clearance_and_height(new_angle, position, actor, 0x20) << 16) <= 0) {
                    TileObject *retry_target = &reference_tile_object;

                    actor->facing = get_rounded_facing_and_rounding_flag(
                        position->tile_x, position->tile_y,
                        retry_target->tile_position.parts.tile_x, retry_target->tile_position.parts.tile_y,
                        &movement_in->action_state_flags);
                }
                {
                    TileObject *check_target = &reference_tile_object;

                    if ((test_neighbor_position_relation(position->tile_x,
                        position->tile_y,
                                       check_target->tile_position.parts.tile_x,
                                       check_target->tile_position.parts.tile_y) << 16) != 0) {
                        near_target = 1;
                    }
                }
            } else {
                select_actor_route_target((u8 *)position, movement_in->unk_9C, (u8 *)actor, &movement_in->action_state_flags);
            }
        }
    } else {
        s32 kind;

        kind = (s8)position->room_index;
        if ((kind >= 0) && (dungeon_rooms[kind].flags & ROOM_HOLY_BEAM)) {
            select_actor_route_target((u8 *)position, movement_in->unk_9C, (u8 *)actor, &movement_in->action_state_flags);
        } else if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            found = probe_directional_neighbor(actor, position->tile_x,
                position->tile_y,
                                  actor->facing);
            if ((found != NULL) && (found->flags1C & ACTOR_PLAYER_SIDE) &&
                (get_actor_height_difference(found, actor) < 0x81) &&
                ((check_diagonal_side_height((actor->facing >> 9) & 0xFFFF,
                                position->tile_x, position->tile_y,
                                (s16)(actor->ground_height - 0x20)) << 16) != 0)) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
            if (actor->flags1C & ACTOR_PLAYER_AWARE) {
                TileObject *target = &reference_tile_object;
                actor->facing = get_rounded_facing_and_rounding_flag(
                    position->tile_x, position->tile_y,
                    target->tile_position.parts.tile_x, target->tile_position.parts.tile_y, &movement_in->action_state_flags);
                if ((test_neighbor_position_relation(position->tile_x, position->tile_y,
                                   target->tile_position.parts.tile_x, target->tile_position.parts.tile_y) << 16) != 0) {
                    if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                        path_result = check_diagonal_side_height(
                            (actor->facing >> 9) & 0xFFFF,
                            position->tile_x, position->tile_y,
                            (s16)(actor->ground_height - 0x20));
                        if ((path_result << 16) != 0) {
                            actor->movement_queue_state &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                select_actor_route_target((u8 *)position, movement_in->unk_9C, (u8 *)actor, &movement_in->action_state_flags);
            }
        }
    }
    attempt = 0;
    x_offsets = (u8 *)((s8 *)dir_step_x);

    do {
        base_angle = actor->facing;
        if (movement_in->action_state_flags & 2) {
            {
                s32 angle_delta = (s32)actor_turn_angle_offsets[attempt];

                move_angle = (s16)(base_angle - angle_delta);
            }
        } else {
            {
                s32 angle_delta = (s32)actor_turn_angle_offsets[attempt];

                move_angle = (s16)(base_angle + angle_delta);
            }
        }
        if ((check_movement_clearance_and_height(move_angle, position, actor, 0x20) << 16) > 0) {
            if (attempt >= 3) {
                target_nearby = near_target;

                if (target_nearby) {
                    actor->movement_queue_state &= 0x7F;
                    return;
                }
            }
            actor->facing = move_angle;
            actor->path_x[actor->movement_queue_state & 0x7F] =
                position->tile_x;
            actor->path_y[actor->movement_queue_state & 0x7F] =
                position->tile_y;
            actor->movement_queue_state++;
            update_map_cell_flags_with_item_limit(position->tile_x, position->tile_y,
                          (actor->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            direction_offset = (actor->facing >> 8) & 0xE;
            position->tile_x +=
                *((u8 *)((u32)direction_offset + (u32)x_offsets));
            position->tile_y += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            next_x = position->tile_x;
            next_y = position->tile_y;
            tile_mask = 0x3000;
            if (actor->flags1C & ACTOR_PLAYER_SIDE) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(next_x, next_y, tile_mask);
            break;
        }
        if (attempt == 0) {
            if ((reference_tile_object.tile_position.word != *(u16 *)&position->tile_x)
                &&
                ((s16)check_entity_relation(actor, NODE_BODY(primary_actor_record->previous_actor_header)) != 0)) {
                return;
            }
        }
        attempt++;
    } while (attempt < 8);
    moved = attempt < 8;
    if (!moved) {
        actor->movement_queue_state &= 0x7F;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor);
        return;
    }
    turn_state = &g_dungeon_status;
    actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    movement_in->unk_9C = position->room_index;
    actor->pending_turn_updates--;
    turn_state->activity_counts.parts.pending_movement_count++;
    if (actor->pending_turn_updates == 0) {
        actor->movement_queue_state &= 0x7F;
        return;
    }

    height_result = sample_terrain_surface_height((position->tile_x << 6) | 0x20,
                      (position->tile_y << 6) | 0x20,
                      (s16)(actor->ground_height - 0x20));
    attempt = height_result;
    if (attempt < 0x200) {
        actor->ground_height = attempt;
    }
    return;

    return;
}
