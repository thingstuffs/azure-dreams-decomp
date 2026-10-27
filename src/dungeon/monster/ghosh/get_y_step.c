/* Ghosh direction-step lookup and queued path movement. */
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/actor_status.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "dungeon/level/room_flags.h"
#include "dungeon/item/actor_target.h"

/* Movement-state fields this handler reads from its first argument.  The +0xB2 selector byte has no field in
 * Rec_func_800A9E70_arg0 (which covers +0x98/+0x9C), so this one handler keeps a minimal local view. */
typedef struct GhoshMoveState {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x15];
    u8 unk_B2;
} GhoshMoveState;

struct ActorRecord; s32 check_entity_relation(struct ActorRecord *, struct ActorRecord *);                     /* extern */
void cycle_map_cell_flags(s16, s16, u16);             /* extern */
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"             /* extern */
s32 check_diagonal_side_height(s32, s16, s16, s16);                /* extern */
s32 check_movement_clearance_and_height();    /* extern */
s32 test_neighbor_position_relation(s32, s32, s32, s32);                  /* extern */
s16 get_actor_height_difference(struct ActorRecord *, struct ActorRecord *);                  /* extern */
u16 get_rounded_facing_and_rounding_flag();          /* extern */
s32 select_actor_route_target(u8 *, s32, u8 *, u16 *);  /* extern */
s32 update_actor_proximity_flag(void *, void *, s32, s32, s8 *); /* extern */
s32 generate_random_value(void);                            /* extern */
void update_actor_status_and_mp(struct ActorRecord *);                      /* extern */
s16 sample_terrain_surface_height();                   /* extern */
s32 begin_ghosh_front_attack();          /* extern */
typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 tail[6];
} D_800E2970Entry;
extern s16 actor_turn_angle_offsets[];
extern s16 D_8006CCD8[8];
extern u16 reference_tile_position_alias;
extern D_800E2970Entry dungeon_rooms[];

/* Returns the unsigned byte at the supplied byte offset in dir_step_y. */
static __inline__ u8 get_y_step(s16 byte_offset) {
    return ((u8 *)dir_step_y)[byte_offset];
}

/* Selects a movement direction and advances the actor path through available tiles. */
/* Chooses a clear path step toward a player-relative tile or nearby actor, records the path, and updates
 * occupancy. */
void advance_actor_path(GhoshMoveState *motion, ObjectPosition *context, SpriteFrameState *position, ActorRecord *actor) {
    s32 turn_index;
    s32 near_target;
    u8 *x_offsets;
    s32 old_tile_mask;
    s32 new_tile_mask;
    s32 target_y;
    s32 target_x;
    s32 y_offset;
    s32 world_y;
    s32 world_x;
    s16 target_angle;
    s16 actor_distance;
    u16 tile_x_or_offset;
    u8 *x_offset_ptr;
    s32 move_value;
    u32 initialized_bit;
    s32 actor_flags;
    s32 direction_offset;
    s32 result;
    s8 tile_index;
    s32 state_flags;
    MovingTile *target_position;
    void *x_offset;
    u8 * active_actor;
    s32 path_status;
    s32 tile_y;
    s32 first_tile_y;
    s32 current_angle;
    s16 candidate_angle;
    u16 *motion_flags;
    s32 source_x;
    s32 source_y;
    s32 dest_x;
    s32 dest_y;
    s32 new_tile_flags;
    s32 step_y;
    s32 next_x;
    s16 current_x;
    s16 next_path_index;
    s32 current_y;
    u8 *world_position;

    state_flags = g_dungeon_status.flags;
    near_target = 0;
    if ((state_flags & 0x4000) || ((s8)actor->movement_queue_state >= 0)) {
        if ((actor->unk_12 >= 2U) || ((begin_ghosh_front_attack(motion, context, position, actor) << 0x10)
            == 0)) {
            update_actor_status_and_mp(actor);
            return;
        }
        active_actor = (u8 *)g_dungeon_status.active_actor;
        if ((void *)active_actor == actor) {
            path_status = 0xC008;
            actor->action_flags = path_status;
            return;
        }
        return;
    }
    if (state_flags & 0x2000) {
        update_actor_proximity_flag(position, actor, 3, 6, &motion->unk_9C);
        actor_flags = actor->flags1C;
        if (actor_flags & 0x410) {
            if (actor_flags & 0x400) {
                initialized_bit = (s32)(find_adjacent_actor(actor, position->tile_x, position->tile_y));
                if ((void *)initialized_bit != NULL) {
                    source_x = position->tile_x;
                    target_position = ((SpriteLinkPrefixView *)(void *)initialized_bit)[-1].sprite;
                    source_y = position->tile_y;
                    dest_x = target_position->tile_x;
                    dest_y = target_position->tile_y;
                    motion_flags = &motion->unk_98;
                    actor->facing = get_rounded_facing_and_rounding_flag(source_x, source_y, dest_x, dest_y, motion_flags);
                    actor->movement_queue_state &= 0x7F;
                    return;
                }
                move_value = actor->flags14;
                if (move_value >= 0) {
                    initialized_bit = 0x80000000;
                    move_value |= initialized_bit;
                    actor->flags14 = move_value;
                    result = generate_random_value();
                    actor->facing += (result & 7) << 9;
                }
            } else {
                x_offset = probe_directional_neighbor(actor, position->tile_x, position->tile_y,
                    actor->facing);
                if (x_offset != NULL) {
                    actor->movement_queue_state &= 0x7F;
                    return;
                }
            }
        } else if (motion->unk_B2 != 0) {
            if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
                if (actor_flags & 0x20000) {
                    direction_offset = ((((u8 *)&actor->unk_44)[1] + (primary_actor_record->facing >> 9)) & 7) * 2;
                    world_x = reference_tile_object.tile_position.parts.tile_x;
                    world_y = reference_tile_object.tile_position.parts.tile_y;
                    x_offset = (void *)(*(u16 *)((u8 *)(((s32 *)dir_step_x)) + direction_offset));
                    y_offset = (*(u16 *)((u8 *)(((s32 *)dir_step_y)) + direction_offset));
                    current_x = position->tile_x;
                    target_x = world_x + ((s32)x_offset);
                    target_y = world_y + y_offset;
                    if ((current_x != (target_x & 0xFFFF)) || (position->tile_y != (target_y & 0xFFFF))) {
                        target_angle = get_rounded_facing_and_rounding_flag(position->tile_x, position->tile_y, (s16) target_x,
                            (s16) target_y, &motion->unk_98);
                        actor->facing = target_angle;
                        if ((check_movement_clearance_and_height(target_angle, position, actor, 0x20) << 0x10) <= 0) {
                            u8 *fallback_position;

                            fallback_position = (u8 *)&reference_tile_position_alias - 0x24;
                            actor->facing = get_rounded_facing_and_rounding_flag(position->tile_x,
                                position->tile_y, fallback_position[0x24], fallback_position[0x25],
                                &motion->unk_98);
                        }
                        world_position = (u8 *)&reference_tile_position_alias - 0x24;
                        result = test_neighbor_position_relation(position->tile_x, position->tile_y, world_position[0x24],
                            world_position[0x25]);
                        if ((result << 0x10) != 0) {
                            near_target = 1;
                        }
                    } else {
                        actor->movement_queue_state &= 0x7F;
                        return;
                    }
                } else {
                    select_actor_route_target((u8 *)position, motion->unk_9C, (u8 *)actor, &motion->unk_98);
                }
            }
        } else {
            tile_index = position->room_index;
            if ((tile_index < 0) || !(dungeon_rooms[tile_index].flags & ROOM_HOLY_BEAM)) {
                if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
                    initialized_bit = (s32)(probe_directional_neighbor(actor, position->tile_x, position->tile_y,
                        actor->facing));
                    if (((void *)initialized_bit == NULL)
                        || !(((ActorRecord *)initialized_bit)->flags1C & ACTOR_PLAYER_SIDE)
                        || (get_actor_height_difference((void *)initialized_bit, actor) >= 0x81)
                        || ((check_diagonal_side_height((actor->facing >> 9) & 0xFFFF,
                        position->tile_x, position->tile_y,
                        (s16)(actor->ground_height - 0x20)) << 0x10) == 0)) {
                        if (actor->flags1C & ACTOR_PLAYER_AWARE) {
                            TileObject *world_origin;

                            world_origin = &reference_tile_object;
                            actor->facing = get_rounded_facing_and_rounding_flag(position->tile_x,
                                position->tile_y, world_origin->tile_position.parts.tile_x, world_origin->tile_position.parts.tile_y, &motion->unk_98);
                            if ((test_neighbor_position_relation(position->tile_x, position->tile_y, world_origin->tile_position.parts.tile_x,
                                world_origin->tile_position.parts.tile_y) << 0x10) != 0) {
                                actor_distance = get_actor_height_difference(primary_actor_record, actor);
                                if (actor_distance < 0x81) {
                                    result = check_diagonal_side_height((actor->facing >> 9) & 0xFFFF, position->tile_x, position->tile_y,
                                        (s16)(actor->ground_height - 0x20));
                                    if ((result << 0x10) != 0) {
                                        actor->movement_queue_state &= 0x7F;
                                        return;
                                    }
                                }
                            } else {
                            }
                        } else {
                            select_actor_route_target((u8 *)position, motion->unk_9C, (u8 *)actor, &motion->unk_98);
                        }
                    } else {
                        actor->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            } else {
                select_actor_route_target((u8 *)position, motion->unk_9C, (u8 *)actor, &motion->unk_98);
            }
        }
        turn_index = 0;
        x_offsets = (u8 *)D_8006CCD8;
        do {
            current_angle = actor->facing;
            if (motion->unk_98 & 2) {
                move_value = actor_turn_angle_offsets[turn_index];
                candidate_angle = current_angle - move_value;
            } else {
                move_value = actor_turn_angle_offsets[turn_index];
                candidate_angle = current_angle + move_value;
            }
            if ((check_movement_clearance_and_height(candidate_angle, position, actor, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    move_value = near_target;
                    if (move_value != 0) {
                        actor->movement_queue_state &= 0x7F;
                        return;
                    }
                }
                actor->facing = candidate_angle;
                ((ActorStatusBytesView *)((u8 *)actor + (actor->movement_queue_state & 0x7F)))->path_x =
                    (u8) position->tile_x;
                ((ActorStatusBytesView *)((u8 *)actor + (actor->movement_queue_state & 0x7F)))->path_y =
                    (u8) position->tile_y;
                next_path_index = actor->movement_queue_state + 1;
                x_offset_ptr = (u8 *)(actor->flags1C & ACTOR_PLAYER_SIDE);
                actor->movement_queue_state = next_path_index;
                tile_x_or_offset = position->tile_x;
                first_tile_y = position->tile_y;
                old_tile_mask = 0x3000;
                if ((s32)x_offset_ptr) {
                    old_tile_mask = 0x300;
                }
                update_map_cell_flags_with_item_limit(tile_x_or_offset, first_tile_y, old_tile_mask);
                tile_x_or_offset = ((u16)actor->facing >> 8) & 0xE;
                x_offset_ptr = (u8 *)((u32) tile_x_or_offset + (u32) x_offsets);
                position->tile_x = (u8) (position->tile_x + *x_offset_ptr);
                current_y = position->tile_y;
                step_y = get_y_step(tile_x_or_offset);
                next_x = position->tile_x;
                position->tile_y = (u8) (current_y + step_y);
                new_tile_mask = 0x3000;
                new_tile_flags = actor->flags1C & ACTOR_PLAYER_SIDE;
                tile_y = position->tile_y;
                if (new_tile_flags) {
                    new_tile_mask = 0x300;
                }
                cycle_map_cell_flags(next_x, tile_y, new_tile_mask);
                break;
            }
            if ((turn_index == 0) && (reference_tile_position_alias != *(u16 *)&position->tile_x)
                && ((check_entity_relation(actor, (struct ActorRecord *)(((s32)primary_actor_record->previous_actor_header) + 0x20)) << 0x10) != 0)) {
                return;
            }
            turn_index += 1;
        } while (turn_index < 8);
        {
            result = turn_index < 8;
            if (result == 0) {
                actor->movement_queue_state &= 0x7F;
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
                update_actor_status_and_mp(actor);
                return;
            }
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            motion->unk_9C = position->room_index;
            actor->pending_turn_updates--;
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
            if (actor->pending_turn_updates == 0) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
            turn_index = sample_terrain_surface_height((position->tile_x << 6) | 0x20, (position->tile_y << 6) | 0x20,
                (s16)(actor->ground_height - 0x20));
            result = turn_index < 0x200;
            if (result != 0) {
                actor->ground_height = turn_index;
            }
            return;
        }
    }
    return;
}
