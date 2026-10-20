#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern s32 check_entity_relation();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s32 check_diagonal_side_height();
extern s32 check_movement_clearance_and_height();
extern s32 compare_monster_neighbor_values();
extern s16 get_actor_height_difference();
extern void *find_valid_monster_neighbor();
extern void *place_actor_at_directional_neighbor();
extern u16 get_rounded_facing_and_rounding_flag();
extern void rebuild_monster_reachable_tiles();
extern void update_actor_proximity_flag();
extern s32 generate_random_value();
extern void update_actor_status_and_food();
extern s16 sample_terrain_surface_height();
extern s32 check_movement_and_initialize_action();
extern s16 D_8006CD00[8];
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
            update_actor_status_and_food(actor);

            return;
        }
        if ((*((void **) ((u8 *)state + 0xC))) == actor) {
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
            target_record = find_valid_monster_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25));
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
            if (place_actor_at_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor + 0x2A)) != 0) {
                *(u8 *)(actor + 0x71) &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                {
                    s32 direction = *(u8 *)(actor + 0x45);
                    s32 base_angle = *((s16 *) (((u8 *) D_800814A8) + 0x2A));
                    s32 direction_offset;
                    s32 target_x;
                    s32 target_y;
                    direction += base_angle >> 9;
                    direction_offset = (direction & 7) * 2;
                    target_x = (D_80082E80.tileX) + (*((u16 *) (((u8 *) (((s8 *)dir_step_x))) + direction_offset)));
                    target_y = (D_80082E80.tileY) + (*((u16 *) (((u8 *) (((s8 *)dir_step_y))) + direction_offset)));
                    if (((*(u8 *)(tile + 0x24)) == ((u16) target_x)) && ((*(u8 *)(tile + 0x25)) == ((u16) target_y))) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                    {
                        u16 next_angle = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), (s16) target_x,
                            (s16) target_y, object + 0x98);
                        *(u16 *)(actor + 0x2A) = next_angle;
                        if ((check_movement_clearance_and_height((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                            *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), object + 0x98);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                    if ((compare_monster_neighbor_values(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(check_goal + 0x24),
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
            if ((tile_kind >= 0) && (D_800E2970[tile_kind].flags & 2)) {
                rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
                    target_record = place_actor_at_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor
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
                    rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
                }
                else {
                    u8 *angle_flags = object + 0x98;
                    *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                        D_80082E80.tileX, D_80082E80.tileY, angle_flags);
                    if ((compare_monster_neighbor_values(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), D_80082E80.tileX, D_80082E80.tileY)
                         << 16) != 0) {
                        if (get_actor_height_difference(D_800814A8, actor) < 0x81) {
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
                base_angle -= D_8006CD00[turn_index];
                angle = base_angle;
            }
            else {
                base_angle += D_8006CD00[turn_index];
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
                if ((*((u16 *) (((u8 *) (((s8 *)&D_80082E80.tileX))) + 0))) != (*(u16 *)(tile + 0x24))) {
                    if ((check_entity_relation(actor, (*((s32 *) (((u8 *) D_800814A8) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

        }
        if (turn_index >= 8) {
            *(u8 *)(actor + 0x71) &= 0x7F;
            *(u16 *)(actor + 0x46) &= 0x7FFF;
            update_actor_status_and_food(actor);
            return;
        }

    }

    *(u16 *)(actor + 0x46) &= 0x7FFF;
    *(u8 *)(object + 0x9C) = *(u8 *)(tile + 0x26);
    (*(u8 *)(actor + 0x6D))--;
    {
        DungeonGlobalStatus *move_state = &g_dungeon_status;
        (((u16)move_state->unk_08))++;
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
