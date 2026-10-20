#include "dungeon/monster/tyrant/update_actor_movement_choosing_direction_recording_path.h"

/* Updates actor movement, choosing a direction and recording its path. */
void update_actor_movement_choosing_direction_recording_path(u8 *move_work, void *entry_context, u8 *position, u8 *actor)
{
    s32 limit_turn;
    s16 step_index;
    s16 *angle_steps;
    DungeonGlobalStatus *state;
    void *target_link;
    u16 state_flags;
    s32 actor_flags;
    s32 current_angle;
    s32 turn_limit;
    s32 trial_angle;
    s32 turn_flags;

    state = &g_dungeon_status;
    state_flags = U16_AT(state, 2);
    limit_turn = 0;

    if ((state_flags & 0x4000) || S8_AT(actor, 0x71) >= 0) {
        if (U8_AT(actor, 0x12) >= 2 ||
            (check_action_eligibility_updates_actor_state_directional_animation_success(move_work, entry_context, position, actor) << 16) == 0) {
            update_actor_status_and_food(actor);
            return;
        }
        if (PTR_AT(state, 0xC) == actor) {
            U16_AT(actor, 0x46) = 0xC008;
        }
        return;
    }

    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, move_work + 0x9C);
    actor_flags = S32_AT(actor, 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_link = find_valid_monster_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
            if (target_link != 0) {
                turn_flags = (s32)PTR_AT(target_link, -0x14);

                U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    U8_AT(turn_flags, 0x24), U8_AT(turn_flags, 0x25), move_work + 0x98);
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }
            {
                turn_flags = S32_AT(actor, 0x14);

                if (!(turn_flags & 0x80000000)) {
                    S32_AT(actor, 0x14) = turn_flags | 0x80000000;
                    turn_limit = generate_random_value();
                    current_angle = U16_AT(actor, 0x2A) + ((turn_limit & 7) << 9);
                    U16_AT(actor, 0x2A) = current_angle;
                }
            }
        } else {
            if (place_actor_at_directional_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                              S16_AT(actor, 0x2A)) != 0) {
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (U16_AT(actor, 0x46) & 0x8000) {
        } else if (!(actor_flags & 0x20000)) {
            rebuild_monster_reachable_tiles(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
        } else {
            {
                s32 direction;
                s32 offset;
                s32 target_x;
                s32 target_y;
                u8 *target = D_80082E80;

                direction = (U8_AT(actor, 0x45) +
                             ((s32)(U16_AT(D_800814A8, 0x2A) << 16) >> 25)) & 7;
                offset = direction * 2;
                target_x = U8_AT(target, 0x24) + U16_AT(((s8 *)dir_step_x), offset);
                target_y = U8_AT(target, 0x25) + U16_AT(((s8 *)dir_step_y), offset);
                if ((U8_AT(position, 0x24) == (u16)target_x) &&
                    (U8_AT(position, 0x25) == (u16)target_y)) {
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                }

                {
                    u8 *angle_work = move_work + 0x98;
                    s16 next_angle = get_rounded_facing_and_rounding_flag(
                        U8_AT(position, 0x24), U8_AT(position, 0x25),
                        (s16)target_x, (s16)target_y, angle_work);

                    U16_AT(actor, 0x2A) = next_angle;
                    if ((check_movement_clearance_and_height(next_angle, position, actor, 0x20) << 16) <= 0) {
                        u8 *fallback = (u8 *)&D_80082EA4 - 0x24;

                        U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                            U8_AT(position, 0x24), U8_AT(position, 0x25),
                            U8_AT(fallback, 0x24), U8_AT(fallback, 0x25), angle_work);
                    }
                }
            }
            {
                u8 *target = (u8 *)&D_80082EA4 - 0x24;

                if ((compare_monster_neighbor_values(
                         U8_AT(position, 0x24), U8_AT(position, 0x25),
                         U8_AT(target, 0x24), U8_AT(target, 0x25)) << 16) != 0) {
                    limit_turn = 1;
                }
            }
        }
    } else {
        s32 tile_kind;
        s32 offset;
        u8 *tile_table;

        tile_kind = S8_AT(position, 0x26);
        if (tile_kind >= 0) {
            tile_table = (u8 *)D_800E2970;
            offset = tile_kind * 0x14;
            offset += (s32)tile_table;
        }
        if (tile_kind >= 0 && (U16_AT((u8 *)offset, 0xC) & 2)) {
            rebuild_monster_reachable_tiles(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
        } else
            if (U16_AT(actor, 0x46) & 0x8000) {
            } else {
                target_link = find_valid_monster_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
                if (!(U16_AT(move_work, 0x98) & 0x8000)) {
                } else if (target_link == 0) {
                } else if ((check_diagonal_side_height(
                         ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                         U8_AT(position, 0x24), U8_AT(position, 0x25),
                         (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                    turn_flags = (s32)PTR_AT(target_link, -0x14);

                    U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                        U8_AT(position, 0x24), U8_AT(position, 0x25),
                        U8_AT(turn_flags, 0x24), U8_AT(turn_flags, 0x25), move_work + 0x98);
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                } else {
                    if (place_actor_at_directional_neighbor(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                                      S16_AT(actor, 0x2A)) != 0) {
                        if ((check_diagonal_side_height(
                                 ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                                 (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                            U8_AT(actor, 0x71) &= 0x7F;
                            return;
                        }
                    }
                    if (!(S32_AT(actor, 0x1C) & 0x20000)) {
                        rebuild_monster_reachable_tiles(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
                    } else {
                        u8 *goal = (u8 *)&D_80082EA4 - 0x24;
                        u8 *angle_work = move_work + 0x98;

                        U16_AT(actor, 0x2A) = get_rounded_facing_and_rounding_flag(
                            U8_AT(position, 0x24), U8_AT(position, 0x25),
                            U8_AT(goal, 0x24), U8_AT(goal, 0x25), angle_work);
                        if ((compare_monster_neighbor_values(
                                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                                 U8_AT(goal, 0x24), U8_AT(goal, 0x25)) << 16) != 0) {
                            if ((check_diagonal_side_height(
                                     ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                                     U8_AT(position, 0x24), U8_AT(position, 0x25),
                                     (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                                U8_AT(actor, 0x71) &= 0x7F;
                                return;
                            }
                        }
                    }
                }
            }
    }

    step_index = 0;
    angle_steps = D_8006CD00;

    for (; step_index < 8; step_index++) {
        current_angle = S16_AT(actor, 0x2A);
        if (U16_AT(move_work, 0x98) & 2) {
            trial_angle = current_angle - angle_steps[step_index];
        } else {
            trial_angle = current_angle + angle_steps[step_index];
        }
        if ((check_movement_clearance_and_height((s16)trial_angle, position, actor, 0x20) << 16) > 0) {
            if (step_index >= 3) {
                turn_limit = limit_turn;
                if (turn_limit != 0) {
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                }
            }
            U16_AT(actor, 0x2A) = trial_angle;
            {
                u8 *path_slot;

                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x74) = U8_AT(position, 0x24);
                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x7C) = U8_AT(position, 0x25);
            }
            U8_AT(actor, 0x71)++;

            update_map_cell_flags_with_item_limit(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);

            {
                s32 move_offset = (U16_AT(actor, 0x2A) >> 8) & 0xE;
                s32 step = (s32)dir_step_x;

                step += move_offset;
                U8_AT(position, 0x24) += *(u8 *)step;
                U8_AT(position, 0x25) += U8_AT(((s8 *)dir_step_y), move_offset);
            }
            cycle_map_cell_flags(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if ((step_index == 0) &&
            (U16_AT(&D_80082EA4, 0) != U16_AT(position, 0x24)) &&
            ((check_entity_relation(
                  actor, S32_AT(D_800814A8, 0x58) + 0x20) << 16) != 0)) {
            return;
        }
    }

    if (step_index >= 8) {
        U8_AT(actor, 0x71) &= 0x7F;
        U16_AT(actor, 0x46) &= 0x7FFF;
        update_actor_status_and_food(actor);
        return;
    }

    U16_AT(actor, 0x46) &= 0x7FFF;
    U8_AT(move_work, 0x9C) = U8_AT(position, 0x26);
    U8_AT(actor, 0x6D)--;
    {
        DungeonGlobalStatus *move_state = &g_dungeon_status;

        U16_AT(move_state, 8)++;
    }
    if (S8_AT(actor, 0x6D) == 0) {
        U8_AT(actor, 0x71) &= 0x7F;
        return;
    }

    step_index = sample_terrain_surface_height(
        (U8_AT(position, 0x24) << 6) | 0x20,
        (U8_AT(position, 0x25) << 6) | 0x20,
        (s16)(U16_AT(actor, 0x88) - 0x20));
    if (step_index < 0x200) {
        U16_AT(actor, 0x88) = step_index;
    }
    return;
}
