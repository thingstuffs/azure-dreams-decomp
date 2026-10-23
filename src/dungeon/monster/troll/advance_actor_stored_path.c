/* Troll path movement, move eligibility checks, and directional animation setup. */
#include "dungeon/monster/troll/advance_actor_stored_path.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/troll.h"

/* Advances the actor along its stored path and updates its movement state. */
void advance_actor_stored_path_2(void *movement, s32 actor_index, void *actor, void *path_state)
{
    void *state = path_state;
    s32 cell_flags;
    s32 move_result;
    s16 heading;
    s32 x;
    s32 y;
    s32 move_kind;
    s32 path_length;
    unsigned long direction_addr;
    u8 *direction_table;
    u8 *current_table;
    u8 *path_entry;

    if (((T_80172CC0_S_80172CC0_0 *)state)->unk_71.s <= 0) {
        return;
    }
    path_length = ((T_80172CC0_S_80172CC0_0 *)state)->unk_71.u;
    if (!(((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s < path_length)) {
        return;
    }

    move_kind = ((T_80172CC0_S_80172CC0_0 *)state)->unk_48;
    switch (move_kind) {
    case 0xD:
        current_table = *(u8 **)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&troll_stored_path_frames;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    case 0xE:
        current_table = *(u8 **)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&D_80175DCC;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    case 0xF:
        current_table = *(u8 **)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&D_80175DD4;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    default:
        break;
    }

    cell_flags = 0x3000;
    x = ((SpriteFrameState *)actor)->tile_x;
    y = ((SpriteFrameState *)actor)->tile_y;
    if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
        cell_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, cell_flags);

    heading = get_rounded_facing_and_rounding_flag(x, y,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_74,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98);
    move_result = (s16)check_movement_clearance_and_height(heading, actor, state, 0x20);

    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    ((SpriteFrameState *)actor)->tile_x = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_74;
    cell_flags = 0x3000;
    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    do {
    } while (0);
    ((SpriteFrameState *)actor)->tile_y = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_7C;
    ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.u++;
    {
        s32 next_x = ((SpriteFrameState *)actor)->tile_x;
        s32 next_y = ((SpriteFrameState *)actor)->tile_y;

        if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
            cell_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, cell_flags);
    }

    ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A = heading;
    if (move_result == 3 && !(g_dungeon_status.flags & 0x80) && !(((SpriteFrameState *)actor)->flags & 0x8000)) {
        reset_actor_directional_animation(movement, actor_index, actor, state);
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    } else {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    }
    (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 0;
        return;
    }

    ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8;
    x = ((T_80172CC0_S_80172CC0_0 *)state)->unk_71.u;
    if (x > 0) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8 / x;
    }
}

/*
 * Chooses Troll's next clear step toward an actor or player-relative tile, records its path, and
 * updates occupancy and height.
 */
void select_and_advance_actor_move(u8 *move_input, void *action_context, u8 *position, u8 *actor) {
    s32 near_target;
    s32 attempt;
    register u8 *x_offsets;
    s32 target_nearby = 0;
    DungeonGlobalStatus *dungeon_state;
    DungeonGlobalStatus *turn_state;
    u32 state_flags;
    u32 actor_flags;
    s32 direction_clear;
    s32 direction_offset;
    s32 move_found;
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    s32 next_y;
    void *found_target;
    u8 *object;

    dungeon_state = &g_dungeon_status;
    state_flags = dungeon_state->flags;
    near_target = 0;

    if ((state_flags & 0x4000) || (((T_80172F58_S_80172F58_1 *)actor)->unk_71.s >= 0)) {
        if ((((T_80172F58_S_80172F58_1 *)actor)->unk_12 >= 2) ||
            ((check_and_prepare_actor_move(move_input, action_context, position, actor) << 16) == 0)) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (dungeon_state->active_actor != actor) {
            return;
        }
        ((T_80172F58_S_80172F58_1 *)actor)->unk_46 = 0xC008;
        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, move_input + 0x9C);
    actor_flags = ((T_80172F58_S_80172F58_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found_target = find_adjacent_actor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v);
            if (found_target != NULL) {
                object = ((T_80172F58_S_80172F58_3_pre *)found_target)[-1].unk_00;
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)get_rounded_facing_and_rounding_flag(
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                    ((T_80172F58_S_80172F58_4 *)object)->unk_24, ((T_80172F58_S_80172F58_4 *)object)->unk_25, move_input + 0x98);
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 object_status;

                s32 random_turn;

                object_status = ((T_80172F58_S_80172F58_1 *)actor)->unk_14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_14 = object_status;
                    random_turn = generate_random_value();
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u += (random_turn & 7) << 9;
                }
            }
        } else {
            found_target = probe_directional_neighbor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                  ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s);
            if (found_target != NULL) {
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((T_80172F58_S_80172F58_1 *)actor)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s32 direction;
                s16 target_x;
                s32 target_y;
                s16 new_angle;
                TileObject *target;

                target = &reference_tile_object;
                direction = (((T_80172F58_S_80172F58_1 *)actor)->unk_45 +
                             ((s32)(((u16)primary_actor_record->facing) << 16) >> 25)) & 7;
                target_x = target->tile_position.parts.tile_x +
                           ((u16 *)((s8 *)dir_step_x))[direction];
                target_y = target->tile_position.parts.tile_y +
                           ((u16 *)((s8 *)dir_step_y))[direction];
                if ((((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v == (u16)target_x) &&
                    (((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v == (u16)target_y)) {
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                new_angle = (u16)get_rounded_facing_and_rounding_flag(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                          target_x, (s16)target_y, move_input + 0x98);
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = new_angle;
                if ((check_movement_clearance_and_height(new_angle, position, actor, 0x20) << 16) <= 0) {
                    TileObject *retry_target = &reference_tile_object;

                    ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)get_rounded_facing_and_rounding_flag(
                        ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                        retry_target->tile_position.parts.tile_x, retry_target->tile_position.parts.tile_y,
                        move_input + 0x98);
                }
                {
                    TileObject *check_target = &reference_tile_object;

                    if ((test_neighbor_position_relation(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                       check_target->tile_position.parts.tile_x,
                                       check_target->tile_position.parts.tile_y) << 16) != 0) {
                        near_target = 1;
                    }
                }
            } else {
                select_actor_route_target(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
            }
        }
    } else {
        s32 kind;

        kind = ((T_80172F58_S_80172F58_2 *)position)->unk_26.s;
        if (kind >= 0 && (((T_80172F58_S_80172F58_9 *)((u8 *)dungeon_rooms + kind * 0x14))->unk_0C & 2)) {
            select_actor_route_target(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
        } else if (!(((T_80172F58_S_80172F58_1 *)actor)->unk_46 & 0x8000)) {
            found_target = probe_directional_neighbor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                  ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s);
            if ((found_target != NULL) && (((T_80172F58_S_80172F58_3 *)found_target)->unk_1C & 0x2000) &&
                (get_actor_height_difference(found_target, actor) < 0x81) &&
                ((check_diagonal_side_height(((s32)(((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20)) << 16) != 0)) {
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            if (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x20000) {
                TileObject *target = &reference_tile_object;
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)get_rounded_facing_and_rounding_flag(
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                    target->tile_position.parts.tile_x, target->tile_position.parts.tile_y, move_input + 0x98);
                if ((test_neighbor_position_relation(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                   target->tile_position.parts.tile_x, target->tile_position.parts.tile_y) << 16) != 0) {
                    if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                        direction_clear = check_diagonal_side_height(
                            ((s32)(((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                            (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20));
                        if ((direction_clear << 16) != 0) {
                            ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                select_actor_route_target(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
            }
        }
    }
    attempt = 0;
    x_offsets = (u8 *)((s8 *)dir_step_x);

    do {
        base_angle = (s32)((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s;
        if (((T_80172F58_S_80172F58_10 *)move_input)->unk_98 & 2) {
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
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
            }
            ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = move_angle;
            ((T_80172F58_S_80172F58_13 *)(actor + (((T_80172F58_S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v;
            ((T_80172F58_S_80172F58_13 *)(actor + (((T_80172F58_S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v;
            ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u++;
            update_map_cell_flags_with_item_limit(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                          (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            direction_offset = (((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u >> 8) & 0xE;
            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v +=
                *((u8 *)((u32)direction_offset + (u32)x_offsets));
            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            next_x = ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v;
            next_y = ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v;
            tile_mask = 0x3000;
            if (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(next_x, next_y, tile_mask);
            break;
        }
        if (attempt == 0) {
            if ((reference_tile_object.tile_position.word != ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00u.v)
                &&
                ((s16)check_entity_relation(actor, ((s32)primary_actor_record->previous_actor_header) + 0x20) != 0)) {
                return;
            }
        }
        attempt++;
    } while (attempt < 8);
    move_found = attempt < 8;
    if (!move_found) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
        ((T_80172F58_S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(actor);
        return;
    }
    turn_state = &g_dungeon_status;
    ((T_80172F58_S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
    ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.u = ((T_80172F58_S_80172F58_2 *)position)->unk_26.u;
    ((T_80172F58_S_80172F58_1 *)actor)->unk_6D.u--;
    turn_state->activity_counts.parts.pending_movement_count++;
    if (((T_80172F58_S_80172F58_1 *)actor)->unk_6D.s == 0) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
        return;
    }
    attempt = sample_terrain_surface_height((((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v << 6) | 0x20,
                      (((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20));
    if (attempt < 0x200) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_88 = attempt;
    }
    return;
}

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void reset_actor_directional_animation(Rec_func_80172CC0_arg0 *state, s32 unused, SpriteFrameState *display, T_80173678_S_80173678_1 *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->unk_9A.as_s8 = 0x10;
    state->unk_9B.as_s8 = 0;
    kind = entity->unk_48;
    switch (kind) {
    case 0xD:
        direction_table = D_80175E9C;
        previous_table = *(u8 **)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xE:
        direction_table = D_80175EA4;
        previous_table = *(u8 **)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xF:
        direction_table = D_80175EAC;
        previous_table = *(u8 **)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}

/* Initializes an actor action and resolves its target and chained effects. */
s32 check_and_prepare_actor_move(void *action_state, s32 facing, void *origin, void *actor)
{
    void *initial_target;
    s32 result = 0;
    s32 range_left;
    s32 next_x;
    s32 next_y;
    u8 origin_x;
    u8 origin_y;

    ((T_80173734_S_80173734_0 *)actor)->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    initial_target = probe_directional_neighbor(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                            ((T_80173734_S_80173734_2 *)origin)->unk_25,
                            ((T_80173734_S_80173734_0 *)actor)->unk_2A);
    if ((check_entity_interaction_compatibility(actor, initial_target) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(((T_80173734_S_80173734_0 *)actor)->unk_46 & 0x8000) &&
        (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(initial_target, actor) + 0x40) >= 0x81) {
        return result;
    }

    result = 1;
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, facing, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    ((T_80173734_S_80173734_3 *)action_state)->unk_9B = 0;
    ((T_80173734_S_80173734_3 *)action_state)->unk_8C = 0;
    ((T_80173734_S_80173734_3 *)action_state)->unk_9A = 0x11;

    switch (((T_80173734_S_80173734_0 *)actor)->unk_48) {
    case 13:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x78;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = 8;
        break;
    case 14:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x70;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = 2;
        break;
    case 15:
        ((T_80173734_S_80173734_0 *)actor)->unk_84 = 0x74;
        ((T_80173734_S_80173734_0 *)actor)->unk_85 = result;
        break;
    }

    ((T_80173734_S_80173734_0 *)actor)->unk_6D--;
    if (((T_80173734_S_80173734_0 *)actor)->unk_48 == 15) {

        ((T_80173734_S_80173734_0 *)actor)->unk_60 =
            scan_actor_along_heading(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                          ((T_80173734_S_80173734_2 *)origin)->unk_25, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 10);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AC = 0;
        if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
            {
                s16 target_distance = get_tile_chebyshev_distance(
                    ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                prepare_directional_attack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, target_distance,
                              ((T_80173734_S_80173734_0 *)actor)->unk_60);
            }

            if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                range_left = 10;
                origin_x = ((T_80173734_S_80173734_2 *)origin)->unk_24;
                origin_y = ((T_80173734_S_80173734_2 *)origin)->unk_25;

loop:
                next_x = ((T_80173734_S_80173734_0 *)actor)->unk_72;
                next_y = ((T_80173734_S_80173734_0 *)actor)->unk_73;
                resolve_attack_damage_and_effects(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A,
                              ((T_80173734_S_80173734_3 *)action_state)->unk_AA);
                range_left -= ((T_80173734_S_80173734_3 *)action_state)->unk_AA;
                if (range_left != 0) {
                    ((T_80173734_S_80173734_2 *)origin)->unk_24 = next_x;
                    ((T_80173734_S_80173734_2 *)origin)->unk_25 = next_y;
                    ((T_80173734_S_80173734_0 *)actor)->unk_60 =
                        scan_actor_along_heading(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                                      ((T_80173734_S_80173734_2 *)origin)->unk_25,
                                      ((T_80173734_S_80173734_0 *)actor)->unk_2A, (s16)range_left);
                    if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
                        ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                        ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
                        {
                            s16 target_distance = get_tile_chebyshev_distance(
                                ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                            ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                            prepare_directional_attack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, target_distance,
                                          ((T_80173734_S_80173734_0 *)actor)->unk_60);
                        }
                        if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                            goto loop;
                        }
                    } else {
                        prepare_directional_attack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
                        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
                    }
                }
                ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
            }
        } else {
            prepare_directional_attack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
            ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
        }

        {
            u32 direction_offset = (((T_80173734_S_80173734_0 *)actor)->unk_6A >> 8) & 0xE;
            setup_object_within_planar_range(
                (u8 *)actor - 0x20,
                (((T_80173734_S_80173734_2 *)origin)->unk_24 << 6) +
                    ((s16)*(u16 *)((u8 *)direction_x_offsets + direction_offset) >> 1) + 0x20,
                (((T_80173734_S_80173734_2 *)origin)->unk_25 << 6) +
                    ((s16)*(u16 *)((u8 *)direction_y_offsets + direction_offset) >> 1) + 0x20,
                ((T_80173734_S_80173734_0 *)actor)->unk_88, 8, 0x300);
        }
    } else {
        prepare_directional_attack(actor, origin, ((T_80173734_S_80173734_0 *)actor)->unk_2A, 1, 0);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
    }

    return result;
}

/* Resolves action targets, updates the actor position, and sets the follow-up state. */
void prepare_actor_path_movement(void *action_input, s32 x_offset_input, void *position_input, void *actor_input)
{
    void *actor = actor_input;
    s32 remaining_steps;
    s32 next_x;
    s32 next_y;
    u32 saved_x;
    u32 saved_y;
    s32 action_state;
    u8 state_param;

    ((T_80173B48_S_80173B48_0 *)actor)->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }

    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, x_offset_input, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return;
    }

    ((T_80173B48_S_80173B48_1 *)action_input)->unk_8C = 0;
    ((T_80173B48_S_80173B48_1 *)action_input)->unk_9A = 0x11;
    ((T_80173B48_S_80173B48_1 *)action_input)->unk_9B = 0;
    ((T_80173B48_S_80173B48_0 *)actor)->unk_6D--;

    if (((T_80173B48_S_80173B48_0 *)actor)->unk_48 == 15) {
        ((T_80173B48_S_80173B48_0 *)actor)->unk_60 =
            scan_actor_along_heading(actor, ((T_80173B48_S_80173B48_2 *)position_input)->unk_24,
                          ((T_80173B48_S_80173B48_2 *)position_input)->unk_25, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 10);
        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AC = 0;
        if (((T_80173B48_S_80173B48_0 *)actor)->unk_60 != 0) {
            {
                s16 travel_steps = get_tile_chebyshev_distance(
                    ((T_80173B48_S_80173B48_3_pre *)(((T_80173B48_S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position_input);
                ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = travel_steps;
                prepare_directional_attack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, travel_steps,
                              ((T_80173B48_S_80173B48_0 *)actor)->unk_60);
            }

            if (((T_80173B48_S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
                remaining_steps = 10;
                saved_x = ((T_80173B48_S_80173B48_2 *)position_input)->unk_24;
                saved_y = ((T_80173B48_S_80173B48_2 *)position_input)->unk_25;

loop:
                next_x = ((T_80173B48_S_80173B48_0 *)actor)->unk_72;
                next_y = ((T_80173B48_S_80173B48_0 *)actor)->unk_73;
                resolve_attack_damage_and_effects(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A,
                              ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA);
                remaining_steps -= ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA;
                if (remaining_steps != 0) {
                    ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = next_x;
                    ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = next_y;
                    ((T_80173B48_S_80173B48_0 *)actor)->unk_60 =
                        scan_actor_along_heading(actor, ((T_80173B48_S_80173B48_2 *)position_input)->unk_24,
                                      ((T_80173B48_S_80173B48_2 *)position_input)->unk_25,
                                      ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, (s16)remaining_steps);
                    if (((T_80173B48_S_80173B48_0 *)actor)->unk_60 != 0) {
                        ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = saved_x;
                        ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = saved_y;
                        {
                            s16 travel_steps = get_tile_chebyshev_distance(
                                ((T_80173B48_S_80173B48_3_pre *)(((T_80173B48_S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position_input);
                            ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = travel_steps;
                            prepare_directional_attack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, travel_steps,
                                          ((T_80173B48_S_80173B48_0 *)actor)->unk_60);
                        }
                        if (((T_80173B48_S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
                            goto loop;
                        }
                    } else {
                        prepare_directional_attack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
                        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
                    }
                }

                ((T_80173B48_S_80173B48_2 *)position_input)->unk_24 = saved_x;
                ((T_80173B48_S_80173B48_2 *)position_input)->unk_25 = saved_y;
            }
        } else {
            prepare_directional_attack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
            ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
        }

        {
            u32 direction_offset = (((T_80173B48_S_80173B48_0 *)actor)->unk_6A >> 8) & 0xE;
            setup_object_within_planar_range(
                (u8 *)actor - 0x20,
                (((T_80173B48_S_80173B48_2 *)position_input)->unk_24 << 6) +
                    ((s16)*(u16 *)((u8 *)direction_x_offsets + direction_offset) >> 1) + 0x20,
                (((T_80173B48_S_80173B48_2 *)position_input)->unk_25 << 6) +
                    ((s16)*(u16 *)((u8 *)direction_y_offsets + direction_offset) >> 1) + 0x20,
                ((T_80173B48_S_80173B48_0 *)actor)->unk_88, 8, 0x300);
        }
    } else {
        prepare_directional_attack(actor, position_input, ((T_80173B48_S_80173B48_0 *)actor)->unk_2A, 1, 0);
        ((T_80173B48_S_80173B48_1 *)action_input)->unk_AA = 1;
    }

    action_state = ((T_80173B48_S_80173B48_0 *)actor)->unk_48;
    switch (action_state) {
    case 13:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x78;
        state_param = 8;
        break;
    case 14:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x70;
        state_param = 2;
        break;
    case 15:
        ((T_80173B48_S_80173B48_0 *)actor)->unk_84 = 0x74;
        state_param = 1;
        break;
    default:
        return;
    }
    ((T_80173B48_S_80173B48_0 *)actor)->unk_85 = state_param;

    return;
}
