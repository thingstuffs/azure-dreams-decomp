#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/monster/nyuel.h"
#include "dungeon/item.h"

extern s32 check_entity_relation();
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s32 check_movement_clearance_and_height();
extern s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
extern s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
extern void * find_adjacent_actor(void *entity, u16 x, u16 y);
extern void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction);
extern void select_actor_route_target();
extern s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 sample_terrain_surface_height();
extern s16 actor_turn_angle_offsets[8];
/* Updates actor movement, recording the path and refreshing the tile position and height. */
void update_actor_movement_and_tile_position(ActorRecord *object, ObjectPosition *entry_context, SpriteFrameState *tile, ActorRecord *actor) {
    DungeonGlobalStatus *state = &g_dungeon_status;
    s32 actor_flags;
    s32 base_angle;
    s32 random_turn;
    s16 limit_turn;
    s16 turn_index;
    s16 angle;
    u16 state_flags;
    void *target_record;
    u8 *target_tile;
    state_flags = state->flags;
    limit_turn = 0;
    if ((state_flags & 0x4000) || (s8)actor->movement_queue_state >= 0) {
        if (actor->unk_12 >= 2 || (check_movement_and_initialize_action(object, entry_context, tile, actor) << 16) == 0) {
            update_actor_status_and_mp(actor);

            return;
        }
        if ((state->active_actor) == actor) {
            actor->action_flags = 0xC008;
        }

        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(tile, actor, 3, 6, &object->unk_9C);
    actor_flags = actor->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_record = find_adjacent_actor(actor, tile->tile_x, tile->tile_y);
            if (target_record != 0) {
                target_tile = *((void **) (((u8 *) target_record) + (-0x14)));
                actor->facing = get_rounded_facing_and_rounding_flag(tile->tile_x, tile->tile_y, *(u8 *)(target_tile
                    + 0x24), *(u8 *)(target_tile + 0x25), &object->action_state_flags);
                {
                    u8 path_length = actor->movement_queue_state & 0x7F;
                    actor->movement_queue_state = path_length;
                }
                return;
            }
            {
                s32 actor_state = actor->flags14;
                base_angle = 0x80000000;
                if (actor_state >= 0) {
                    actor_state = base_angle | actor_state;
                    actor->flags14 = actor_state;

                    random_turn = generate_random_value();
                    (*(u16 *)&actor->facing) += (random_turn & 7) << 9;
                }
            }
        }
        else {
            if (probe_directional_neighbor(actor, tile->tile_x, tile->tile_y, actor->facing) != 0) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!(actor->action_flags & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                select_actor_route_target(tile, object->unk_9C, actor, &object->action_state_flags);
            }
            else {
                {
                    s32 direction = *(u8 *)(((u8 *)actor + 0x45));
                    s32 player_angle = *((s16 *) (((u8 *) primary_actor_record) + 0x2A));
                    s32 direction_offset;
                    s32 target_x;
                    s32 target_y;
                    direction += player_angle >> 9;
                    direction_offset = (direction & 7) * 2;
                    target_x = (reference_tile_object.tile_position.parts.tile_x) + (*((u16 *) (((u8 *) (((s8 *)dir_step_x))) + direction_offset)));
                    target_y = (reference_tile_object.tile_position.parts.tile_y) + (*((u16 *) (((u8 *) (((s8 *)dir_step_y))) + direction_offset)));
                    if ((tile->tile_x == ((u16) target_x)) && (tile->tile_y == ((u16) target_y))) {
                        actor->movement_queue_state &= 0x7F;
                        return;
                    }
                    {
                        u16 next_angle = get_rounded_facing_and_rounding_flag(tile->tile_x, tile->tile_y, (s16) target_x,
                            (s16) target_y, &object->action_state_flags);
                        actor->facing = next_angle;
                        if ((check_movement_clearance_and_height((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) - 0x24;
                            actor->facing = get_rounded_facing_and_rounding_flag(tile->tile_x, tile->tile_y,
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), &object->action_state_flags);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) - 0x24;
                    if ((test_neighbor_position_relation(tile->tile_x, tile->tile_y, *(u8 *)(check_goal + 0x24),
                        *(u8 *)(check_goal + 0x25)) << 16) != 0) {
                        limit_turn = 1;
                    }
                }
            }
        }
    }
    else {
        {
            s8 tile_kind = (s8)tile->room_index;
            if ((tile_kind >= 0) && (dungeon_rooms[tile_kind].flags & 2)) {
                select_actor_route_target(tile, object->unk_9C, actor, &object->action_state_flags);
            }
            else {
                if (!(actor->action_flags & 0x8000)) {
                    target_record = probe_directional_neighbor(actor, tile->tile_x, tile->tile_y, actor->facing);
                    if (target_record != 0) {
                        if ((*((s32 *) (((u8 *) target_record) + 0x1C))) & 0x2000) {
                            if (get_actor_height_difference(target_record, actor) < 0x81) {
                                if ((check_diagonal_side_height((actor->facing >> 9) & 0xFFFF, tile->tile_x,
                                    tile->tile_y, (s16) ((u16)actor->ground_height - 0x20)) << 16) != 0) {
                                    actor->movement_queue_state &= 0x7F;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (!(actor->flags1C & 0x20000)) {
                    select_actor_route_target(tile, object->unk_9C, actor, &object->action_state_flags);
                }
                else {
                    u16 *angle_flags = &object->action_state_flags;
                    actor->facing = get_rounded_facing_and_rounding_flag(tile->tile_x, tile->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_flags);
                    if ((test_neighbor_position_relation(tile->tile_x, tile->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)
                         << 16) != 0) {
                        if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                            if ((check_diagonal_side_height((actor->facing >> 9) & 0xFFFF, tile->tile_x,
                                tile->tile_y, (s16) ((u16)actor->ground_height - 0x20)) << 16) != 0) {
                                actor->movement_queue_state &= 0x7F;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    {
        turn_index = 0;
        for (; turn_index < 8; turn_index++) {
            base_angle = actor->facing;

            if (object->action_state_flags & 2) {
                base_angle -= actor_turn_angle_offsets[turn_index];
                angle = base_angle;
            }
            else {
                base_angle += actor_turn_angle_offsets[turn_index];
                angle = base_angle;
            }
            if ((check_movement_clearance_and_height((s16) angle, tile, actor, 0x20) << 16) > 0) {
                if (turn_index >= 3) {
                    s32 turn_limited = limit_turn;
                    if (turn_limited) {
                        actor->movement_queue_state &= 0x7F;
                        return;
                    }
                }
                actor->facing = angle;
                *((u8 *) (((u8 *) (((u8 *)actor)+ (actor->movement_queue_state & 0x7F))) + 0x74)) = tile->tile_x;
                *((u8 *) (((u8 *) (((u8 *)actor)+ (actor->movement_queue_state & 0x7F))) + 0x7C)) = tile->tile_y;
                actor->movement_queue_state++;
                update_map_cell_flags_with_item_limit(tile->tile_x, tile->tile_y, (actor->flags1C & 0x2000)
                    ? (0x300) : (0x3000));
                {
                    s32 direction = ((u16)actor->facing >> 8) & 0xE;
                    u8 *step_x = (u8 *)dir_step_x;
                    step_x += direction;
                    tile->tile_x += *step_x;
                    tile->tile_y += *((u8 *) (((u8 *) (((s8 *)dir_step_y))) + direction));
                }
                cycle_map_cell_flags(tile->tile_x, tile->tile_y, (actor->flags1C & 0x2000)
                    ? (0x300) : (0x3000));
                break;
            }
            if (turn_index == 0) {
                if ((*((u16 *) (((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) + 0))) != (*(u16 *)(((u8 *)tile + 0x24)))) {
                    if ((check_entity_relation(actor, (*((s32 *) (((u8 *) primary_actor_record) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

        }
        if (turn_index >= 8) {
            actor->movement_queue_state &= 0x7F;
            actor->action_flags &= 0x7FFF;
            update_actor_status_and_mp(actor);
            return;
        }

    }

    actor->action_flags &= 0x7FFF;
    object->unk_9C = tile->room_index;
    (*(u8 *)&actor->pending_turn_updates)--;
    {
        DungeonGlobalStatus *move_state = &g_dungeon_status;
        move_state->activity_counts.parts.pending_movement_count++;
    }
    if (actor->pending_turn_updates == 0) {
        actor->movement_queue_state &= 0x7F;

        return;
    }
    {
        turn_index = sample_terrain_surface_height((tile->tile_x << 6) | 0x20, (tile->tile_y << 6) | 0x20, (s16) ((u16)actor->ground_height - 0x20));
        if (turn_index < 0x200) {
            actor->ground_height = turn_index;
        }
    }

    return;
    return;

}
