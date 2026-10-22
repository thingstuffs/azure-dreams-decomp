#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 get_entity_effect_value();
extern s32 check_entity_relation();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s32 check_diagonal_side_height();
extern s32 check_directional_move_and_terrain();
extern s32 test_neighbor_position_relation();
extern s16 get_actor_height_difference();
extern void *find_valid_monster_neighbor();
extern void *probe_directional_neighbor();
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void rebuild_monster_reachable_tiles();
extern void update_actor_proximity_flag();
extern s32 generate_random_value();
extern void update_actor_status_and_mp();
extern s16 sample_terrain_surface_height();
extern s32 try_turn_actor_toward_target();

extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern s16 actor_turn_angle_offsets[];

/* Choose a movement direction, move the actor, and update its path history and height. */
/* Chooses U-Boat's next clear step, records its path, and updates tile occupancy unless status slot 27
 * suppresses that update. */
void choose_and_execute_actor_step(void *work_data, void *action_context, u8 *position, u8 *actor) {
    DungeonGlobalStatus *turn_state;
    u16 turn_flags;
    s32 movement_flags;
    s32 limit_turn;
    s32 attempt;
    s16 *angle_step;
    s32 target_x;
    s32 target_y;
    s32 candidate_angle;
    s32 call_result;
    s32 tile_mask;
    s16 direction_offset;
    s32 direction;
    s32 tile_type;
    s32 work_value;
    void *node;
    void *parent;

    turn_state = &g_dungeon_status;
    turn_flags = turn_state->flags;
    limit_turn = turn_flags & 0;

    if ((turn_flags & 0x4000) || (S8_AT(actor, 0x71) >= 0)) {
        if ((U8_AT(actor, 0x12) >= 2) || U8_AT(work_data, 0xB5) ||
            ((try_turn_actor_toward_target(work_data, action_context, position, actor) << 16) == 0)) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (turn_state->active_actor == actor) {
            U16_AT(actor, 0x46) = 0xC008;
        }
        return;
    }

    if ((turn_flags & 0x2000) == 0) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, (u8 *)work_data + 0x9C);
    movement_flags = S32_AT(actor, 0x1C);

    if (movement_flags & 0x410) {
        if (movement_flags & 0x400) {
            node = find_valid_monster_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
            if (node != NULL) {
                u8 *node_work;
                s32 history_index;

                parent = PTR_AT(node, -0x14);
                node_work = (u8 *)work_data + 0x98;
                U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    U8_AT(parent, 0x24), U8_AT(parent, 0x25),
                    node_work);
                history_index = U8_AT(actor, 0x71);
                history_index &= 0x7F;
                U8_AT(actor, 0x71) = history_index;
                return;
            }

            work_value = S32_AT(actor, 0x14);
            if (!(work_value & 0x80000000)) {
                S32_AT(actor, 0x14) = work_value | 0x80000000;
                call_result = generate_random_value();
                U16_AT(actor, 0x2A) += (call_result & 7) << 9;
            }
        } else {
            work_value = (s32)probe_directional_neighbor(actor, U8_AT(position, 0x24),
                                            U8_AT(position, 0x25),
                                            S16_AT(actor, 0x2A));
            if (work_value != 0) {
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }
        }
    } else if (movement_flags & 0x2000) {
        if (!(U16_AT(actor, 0x46) & 0x8000)) {
            if (movement_flags & 0x20000) {
            s16 path_angle;
            TileObject *path_center;
            u8 *path_work;

            path_center = &reference_tile_object;
            direction = (U8_AT(actor, 0x45) + (S16_AT(primary_actor_record, 0x2A) >> 9)) & 7;
            target_x = path_center->tile_position.parts.tile_x +
                       *(u16 *)(D_8006CCD8 + (direction * 2));
            target_y = path_center->tile_position.parts.tile_y +
                       *(u16 *)(D_8006CCE8 + (direction * 2));

            if ((U8_AT(position, 0x24) == (u16)target_x) &&
                (U8_AT(position, 0x25) == (u16)target_y)) {
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }

            path_work = (u8 *)work_data + 0x98;
            path_angle = get_rounded_facing_and_rounding_flag(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (s16)target_x, (s16)target_y, path_work);
            U16_AT(actor, 0x2A) = path_angle;
            call_result = check_directional_move_and_terrain(path_angle, position, actor, 0x20);
            if ((call_result << 16) <= 0) {
                U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y, path_work);
            }

            work_value = test_neighbor_position_relation(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y);
            attempt = 0;
            if ((work_value << 16) != 0) {
                limit_turn = 1;
            }
            } else {
                rebuild_monster_reachable_tiles(position, S8_AT(work_data, 0x9C), actor, (u8 *)work_data + 0x98);
            }
        }
    } else {
        u8 *tile_records;
        u8 *tile_record;

        tile_type = S8_AT(position, 0x26);
        if (tile_type >= 0 && (tile_records = dungeon_rooms, tile_record = tile_records + tile_type * 0x14,
            U16_AT(tile_record, 0xC) & 2)) {
            rebuild_monster_reachable_tiles(position, S8_AT(work_data, 0x9C), actor, (u8 *)work_data + 0x98);
        } else if (!(U16_AT(actor, 0x46) & 0x8000)) {
            node = probe_directional_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                                 S16_AT(actor, 0x2A));
            if ((node != NULL) && (S32_AT(node, 0x1C) & 0x2000) &&
                (get_actor_height_difference(node, actor) < 0x81) &&
                ((check_diagonal_side_height(
                      ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                      U8_AT(position, 0x24), U8_AT(position, 0x25),
                      (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0)) {
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }

            if (S32_AT(actor, 0x1C) & 0x20000) {
                TileObject *move_center;

                move_center = &reference_tile_object;
                U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    move_center->tile_position.parts.tile_x, move_center->tile_position.parts.tile_y,
                    (u8 *)work_data + 0x98);

                if ((test_neighbor_position_relation(
                        U8_AT(position, 0x24), U8_AT(position, 0x25),
                        move_center->tile_position.parts.tile_x, move_center->tile_position.parts.tile_y) << 16) != 0) {
                    if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                        if ((check_diagonal_side_height(
                                ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                                U8_AT(position, 0x24), U8_AT(position, 0x25),
                                (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                            U8_AT(actor, 0x71) &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                rebuild_monster_reachable_tiles(position, S8_AT(work_data, 0x9C), actor, (u8 *)work_data + 0x98);
            }
        }
    }

    attempt = 0;
    work_value = (s32)0x80070000;
    angle_step = actor_turn_angle_offsets;

    do {
        node = (void *)S16_AT(actor, 0x2A);
        if (U16_AT(work_data, 0x98) & 2) {
            candidate_angle = ((s32)node) - *angle_step;
        } else {
            candidate_angle = ((s32)node) + *angle_step;
        }

        call_result = check_directional_move_and_terrain((s16)candidate_angle, position, actor, 0x20);
        if ((call_result << 16) > 0) {
            if (attempt >= 3) {
                work_value = limit_turn;
                if (work_value != 0) {
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                }
            }

            U16_AT(actor, 0x2A) = candidate_angle;
            U8_AT((u8 *)actor + (U8_AT(actor, 0x71) & 0x7F), 0x74) =
                U8_AT(position, 0x24);
            U8_AT((u8 *)actor + (U8_AT(actor, 0x71) & 0x7F), 0x7C) =
                U8_AT(position, 0x25);
            U8_AT(actor, 0x71)++;

            call_result = get_entity_effect_value(actor, 0x1B);
            if ((call_result << 16) == 0) {
                s32 old_x;
                s32 old_y;

                old_x = U8_AT(position, 0x24);
                old_y = U8_AT(position, 0x25);
                tile_mask = 0x3000;
                if (S32_AT(actor, 0x1C) & 0x2000) {
                    tile_mask = 0x300;
                }
                update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);
            }

            {
                s8 position_x;
                u8 *table;

                direction_offset = (U16_AT(actor, 0x2A) >> 8) & 0xE;
                position_x = U8_AT(position, 0x24);
                table = D_8006CCD8;
                table += direction_offset;
                position_x += *table;
                U8_AT(position, 0x24) = position_x;
                U8_AT(position, 0x25) += D_8006CCE8[direction_offset];
            }

            if ((call_result << 16) == 0) {
                s32 new_x;
                s32 new_y;

                new_x = U8_AT(position, 0x24);
                new_y = U8_AT(position, 0x25);
                tile_mask = 0x3000;
                if (S32_AT(actor, 0x1C) & 0x2000) {
                    tile_mask = 0x300;
                }
                cycle_map_cell_flags(new_x, new_y, tile_mask);
            }
            break;
        }
        if (attempt == 0) {
            if (*(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != U16_AT(position, 0x24)) {
                if ((check_entity_relation(actor, S32_AT(primary_actor_record, 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
        }
        attempt++;
        angle_step++;
    } while (attempt < 8);
    if (attempt >= 8) {
        U8_AT(actor, 0x71) &= 0x7F;
        U16_AT(actor, 0x46) &= 0x7FFF;
        update_actor_status_and_mp(actor);
        return;
    }

    U16_AT(actor, 0x46) &= 0x7FFF;
    S8_AT(work_data, 0x9C) = U8_AT(position, 0x26);
    U8_AT(actor, 0x6D)--;
    {
        DungeonGlobalStatus *turn_state_tail = &g_dungeon_status;

        U16_AT(turn_state_tail, 8)++;
    }
    if (S8_AT(actor, 0x6D) == 0) {
        U8_AT(actor, 0x71) &= 0x7F;
        return;
    }
    attempt = sample_terrain_surface_height(
        (U8_AT(position, 0x24) << 6) | 0x20,
        (U8_AT(position, 0x25) << 6) | 0x20,
        (s16)(U16_AT(actor, 0x88) - 0x20));
    if (attempt < 0x200) {
        U16_AT(actor, 0x88) = attempt;
    }
    return;
}
