#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/monster/nyuel.h"

extern s32 check_entity_relation();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s32 check_diagonal_side_height();
extern s32 check_movement_clearance_and_height();
extern s32 test_neighbor_position_relation();
extern s16 get_actor_height_difference();
extern void *find_adjacent_actor();
extern void *probe_directional_neighbor();
extern u16 get_rounded_facing_and_rounding_flag();
extern void select_actor_route_target();
extern void update_actor_proximity_flag();
extern s32 generate_random_value();
extern void update_actor_status_and_mp();
extern s16 sample_terrain_surface_height();
extern s16 actor_turn_angle_offsets[8];
/* Updates actor movement, recording the path and refreshing the tile position and height. */
void update_actor_movement_and_tile_position(u8 *object, void *entry_context, u8 *tile, u8 *actor)
{
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
    if ((state_flags & 0x4000) || (*(s8 *)(actor + 0x71)) >= 0) {
        if ((*(u8 *)(actor + 0x12)) >= 2 || (check_movement_and_initialize_action(object, entry_context, tile, actor) << 16) == 0) {
            update_actor_status_and_mp(actor);

            return;
        }
        if ((state->active_actor) == actor) {
            *(u16 *)(actor + 0x46) = 0xC008;
        }

        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(tile, actor, 3, 6, object + 0x9C);
    actor_flags = *(s32 *)(actor + 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_record = find_adjacent_actor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25));
            if (target_record != 0) {
                target_tile = *((void **) (((u8 *) target_record) + (-0x14)));
                *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(target_tile
                    + 0x24), *(u8 *)(target_tile + 0x25), object + 0x98);
                {
                    u8 path_length = (*(u8 *)(actor + 0x71)) & 0x7F;
                    *(u8 *)(actor + 0x71) = path_length;
                }
                return;
            }
            {
                s32 actor_state = *(s32 *)(actor + 0x14);
                base_angle = 0x80000000;
                if (actor_state >= 0) {
                    actor_state = base_angle | actor_state;
                    *(s32 *)(actor + 0x14) = actor_state;

                    random_turn = generate_random_value();
                    *(u16 *)(actor + 0x2A) += (random_turn & 7) << 9;
                }
            }
        }
        else {
            if (probe_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor + 0x2A)) != 0) {
                *(u8 *)(actor + 0x71) &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                select_actor_route_target(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                {
                    s32 direction = *(u8 *)(actor + 0x45);
                    s32 base_angle = *((s16 *) (((u8 *) primary_actor_record) + 0x2A));
                    s32 direction_offset;
                    s32 target_x;
                    s32 target_y;
                    direction += base_angle >> 9;
                    direction_offset = (direction & 7) * 2;
                    target_x = (reference_tile_object.tile_position.parts.tile_x) + (*((u16 *) (((u8 *) (((s8 *)dir_step_x))) + direction_offset)));
                    target_y = (reference_tile_object.tile_position.parts.tile_y) + (*((u16 *) (((u8 *) (((s8 *)dir_step_y))) + direction_offset)));
                    if (((*(u8 *)(tile + 0x24)) == ((u16) target_x)) && ((*(u8 *)(tile + 0x25)) == ((u16) target_y))) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                    {
                        u16 next_angle = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), (s16) target_x,
                            (s16) target_y, object + 0x98);
                        *(u16 *)(actor + 0x2A) = next_angle;
                        if ((check_movement_clearance_and_height((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) - 0x24;
                            *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), object + 0x98);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) - 0x24;
                    if ((test_neighbor_position_relation(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(check_goal + 0x24),
                        *(u8 *)(check_goal + 0x25)) << 16) != 0) {
                        limit_turn = 1;
                    }
                }
            }
        }
    }
    else {
        {
            s8 tile_kind = *(s8 *)(tile + 0x26);
            if ((tile_kind >= 0) && (dungeon_rooms[tile_kind].flags & 2)) {
                select_actor_route_target(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
                    target_record = probe_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor
                        + 0x2A));
                    if (target_record != 0) {
                        if ((*((s32 *) (((u8 *) target_record) + 0x1C))) & 0x2000) {
                            if (get_actor_height_difference(target_record, actor) < 0x81) {
                                if ((check_diagonal_side_height(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                    *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                    *(u8 *)(actor + 0x71) &= 0x7F;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (!((*(s32 *)(actor + 0x1C)) & 0x20000)) {
                    select_actor_route_target(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
                }
                else {
                    u8 *angle_flags = object + 0x98;
                    *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_flags);
                    if ((test_neighbor_position_relation(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)
                         << 16) != 0) {
                        if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                            if ((check_diagonal_side_height(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                *(u8 *)(actor + 0x71) &= 0x7F;
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
            base_angle = *(s16 *)(actor + 0x2A);

            if ((*(u16 *)(object + 0x98)) & 2) {
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
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                }
                *(u16 *)(actor + 0x2A) = angle;
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x74)) = *(u8 *)(tile + 0x24);
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x7C)) = *(u8 *)(tile + 0x25);
                (*(u8 *)(actor + 0x71))++;
                update_map_cell_flags_with_item_limit(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                {
                    s32 direction = ((*(u16 *)(actor + 0x2A)) >> 8) & 0xE;
                    u8 *step_x = (u8 *)dir_step_x;
                    step_x += direction;
                    *(u8 *)(tile + 0x24) += *step_x;
                    *(u8 *)(tile + 0x25) += *((u8 *) (((u8 *) (((s8 *)dir_step_y))) + direction));
                }
                cycle_map_cell_flags(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                break;
            }
            if (turn_index == 0) {
                if ((*((u16 *) (((u8 *) (((s8 *)&reference_tile_object.tile_position.parts.tile_x))) + 0))) != (*(u16 *)(tile + 0x24))) {
                    if ((check_entity_relation(actor, (*((s32 *) (((u8 *) primary_actor_record) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

        }
        if (turn_index >= 8) {
            *(u8 *)(actor + 0x71) &= 0x7F;
            *(u16 *)(actor + 0x46) &= 0x7FFF;
            update_actor_status_and_mp(actor);
            return;
        }

    }

    *(u16 *)(actor + 0x46) &= 0x7FFF;
    *(u8 *)(object + 0x9C) = *(u8 *)(tile + 0x26);
    (*(u8 *)(actor + 0x6D))--;
    {
        DungeonGlobalStatus *move_state = &g_dungeon_status;
        move_state->activity_counts.parts.pending_movement_count++;
    }
    if ((*(s8 *)(actor + 0x6D)) == 0) {
        *(u8 *)(actor + 0x71) &= 0x7F;

        return;
    }
    {
        turn_index = sample_terrain_surface_height(((*(u8 *)(tile + 0x24)) << 6) | 0x20, ((*(u8 *)(tile
            + 0x25)) << 6) | 0x20, (s16) ((*(u16 *)(actor + 0x88)) - 0x20));
        if (turn_index < 0x200) {
            *(u16 *)(actor + 0x88) = turn_index;
        }
    }

    return;
    return;

}
