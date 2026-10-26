#include "shared/entity.h"
/* Troll path movement, move eligibility checks, and directional animation setup. */
#include "dungeon/monster/troll/advance_actor_stored_path.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/troll.h"

/* Advances the actor along its stored path and updates its movement state. */
void advance_actor_stored_path_2(ActorRecord *movement, ObjectPosition *actor_index, SpriteFrameState *actor, ActorRecord *path_state) {
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
        current_table = ((SpriteFrameState *)actor)->frameTable;
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
        current_table = ((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&troll_frame_set;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    case 0xF:
        current_table = ((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&troll_frame_set_4;
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
        &movement->action_state_flags);
    move_result = (s16)check_movement_clearance_and_height(heading, actor, state, 0x20);

    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    ((SpriteFrameState *)actor)->tile_x = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_74;
    cell_flags = 0x3000;
    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_80CE94C0). */
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
void select_and_advance_actor_move(ActorRecord *move_input, ObjectPosition *action_context, SpriteFrameState *position, ActorRecord *actor) {
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
    ActorRecord *found_target;
    SpriteFrameState *object;

    dungeon_state = &g_dungeon_status;
    state_flags = dungeon_state->flags;
    near_target = 0;

    if ((state_flags & 0x4000) || ((s8)actor->movement_queue_state >= 0)) {
        if ((actor->unk_12 >= 2) ||
            ((check_and_prepare_actor_move(move_input, action_context, position, actor) << 16) == 0)) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (dungeon_state->active_actor != actor) {
            return;
        }
        actor->action_flags = 0xC008;
        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, &move_input->unk_9C);
    actor_flags = actor->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found_target = find_adjacent_actor(actor, position->tile_x,
                position->tile_y);
            if (found_target != NULL) {
                object = ((ObjectNodeHeader *)found_target - 1)->sprite;
                actor->facing = (u16)get_rounded_facing_and_rounding_flag(
                    position->tile_x, position->tile_y,
                    object->tile_x, object->tile_y, &move_input->action_state_flags);
                actor->movement_queue_state &= 0x7F;
                return;
            }
            {
                s32 object_status;

                s32 random_turn;

                object_status = actor->flags14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    actor->flags14 = object_status;
                    random_turn = generate_random_value();
                    actor->facing += (random_turn & 7) << 9;
                }
            }
        } else {
            found_target = probe_directional_neighbor(actor, position->tile_x,
                position->tile_y,
                                  actor->facing);
            if (found_target != NULL) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s32 direction;
                s16 target_x;
                s32 target_y;
                s16 new_angle;
                TileObject *target;

                target = &reference_tile_object;
                direction = (((u8 *)&actor->unk_44)[1] +
                             (primary_actor_record->facing >> 9)) & 7;
                target_x = target->tile_position.parts.tile_x +
                           ((u16 *)((s8 *)dir_step_x))[direction];
                target_y = target->tile_position.parts.tile_y +
                           ((u16 *)((s8 *)dir_step_y))[direction];
                if ((position->tile_x == (u16)target_x) &&
                    (position->tile_y == (u16)target_y)) {
                    actor->movement_queue_state &= 0x7F;
                    return;
                }
                new_angle = (u16)get_rounded_facing_and_rounding_flag(position->tile_x,
                    position->tile_y,
                                          target_x, (s16)target_y, &move_input->action_state_flags);
                actor->facing = new_angle;
                if ((check_movement_clearance_and_height(new_angle, position, actor, 0x20) << 16) <= 0) {
                    TileObject *retry_target = &reference_tile_object;

                    actor->facing = (u16)get_rounded_facing_and_rounding_flag(
                        position->tile_x, position->tile_y,
                        retry_target->tile_position.parts.tile_x, retry_target->tile_position.parts.tile_y,
                        &move_input->action_state_flags);
                }
                {
                    TileObject *check_target = &reference_tile_object;

                    if ((test_neighbor_position_relation(position->tile_x, position->tile_y,
                                       check_target->tile_position.parts.tile_x,
                                       check_target->tile_position.parts.tile_y) << 16) != 0) {
                        near_target = 1;
                    }
                }
            } else {
                select_actor_route_target(position, move_input->unk_9C, actor, &move_input->action_state_flags);
            }
        }
    } else {
        s32 kind;

        kind = (s8)position->room_index;
        if (kind >= 0 && (dungeon_rooms[kind].flags & ROOM_HOLY_BEAM)) {
            select_actor_route_target(position, move_input->unk_9C, actor, &move_input->action_state_flags);
        } else if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            found_target = probe_directional_neighbor(actor, position->tile_x,
                position->tile_y,
                                  actor->facing);
            if ((found_target != NULL) && (found_target->flags1C & ACTOR_PLAYER_SIDE) &&
                (get_actor_height_difference(found_target, actor) < 0x81) &&
                ((check_diagonal_side_height((actor->facing >> 9) & 0xFFFF,
                                position->tile_x, position->tile_y,
                                (s16)(actor->ground_height - 0x20)) << 16) != 0)) {
                actor->movement_queue_state &= 0x7F;
                return;
            }
            if (actor->flags1C & ACTOR_PLAYER_AWARE) {
                TileObject *target = &reference_tile_object;
                actor->facing = (u16)get_rounded_facing_and_rounding_flag(
                    position->tile_x, position->tile_y,
                    target->tile_position.parts.tile_x, target->tile_position.parts.tile_y, &move_input->action_state_flags);
                if ((test_neighbor_position_relation(position->tile_x, position->tile_y,
                                   target->tile_position.parts.tile_x, target->tile_position.parts.tile_y) << 16) != 0) {
                    if (get_actor_height_difference(primary_actor_record, actor) < 0x81) {
                        direction_clear = check_diagonal_side_height(
                            (actor->facing >> 9) & 0xFFFF,
                            position->tile_x, position->tile_y,
                            (s16)(actor->ground_height - 0x20));
                        if ((direction_clear << 16) != 0) {
                            actor->movement_queue_state &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                select_actor_route_target(position, move_input->unk_9C, actor, &move_input->action_state_flags);
            }
        }
    }
    attempt = 0;
    x_offsets = (u8 *)((s8 *)dir_step_x);

    do {
        base_angle = actor->facing;
        if (move_input->action_state_flags & 2) {
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
            ((ActorStatusBytesView *)((u8 *)actor + (actor->movement_queue_state & 0x7F)))->path_x =
                position->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor + (actor->movement_queue_state & 0x7F)))->path_y =
                position->tile_y;
            actor->movement_queue_state++;
            update_map_cell_flags_with_item_limit(position->tile_x, position->tile_y,
                          (actor->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            direction_offset = ((u16)actor->facing >> 8) & 0xE;
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
                ((s16)check_entity_relation(actor, ((s32)primary_actor_record->previous_actor_header) + 0x20) != 0)) {
                return;
            }
        }
        attempt++;
    } while (attempt < 8);
    move_found = attempt < 8;
    if (!move_found) {
        actor->movement_queue_state &= 0x7F;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor);
        return;
    }
    turn_state = &g_dungeon_status;
    actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    move_input->unk_9C = position->room_index;
    actor->pending_turn_updates--;
    turn_state->activity_counts.parts.pending_movement_count++;
    if (actor->pending_turn_updates == 0) {
        actor->movement_queue_state &= 0x7F;
        return;
    }
    attempt = sample_terrain_surface_height((position->tile_x << 6) | 0x20,
                      (position->tile_y << 6) | 0x20,
                      (s16)(actor->ground_height - 0x20));
    if (attempt < 0x200) {
        actor->ground_height = attempt;
    }
    return;
}

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void reset_actor_directional_animation(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *display, ActorRecord *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->action_id = 0x10;
    state->action_phase = 0;
    kind = entity->unk_48;
    switch (kind) {
    case 0xD:
        direction_table = D_80175E9C;
        previous_table = display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xE:
        direction_table = D_80175EA4;
        previous_table = display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xF:
        direction_table = D_80175EAC;
        previous_table = display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                      0);
    }
}

/* Initializes an actor action and resolves its target and chained effects. */
s32 check_and_prepare_actor_move(ActorRecord *action_state, ObjectPosition *facing, SpriteFrameState *origin, ActorRecord *actor) {
    void *initial_target;
    s32 result = 0;
    s32 range_left;
    s32 next_x;
    s32 next_y;
    u8 origin_x;
    u8 origin_y;

    actor->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    initial_target = probe_directional_neighbor(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                            ((T_80173734_S_80173734_2 *)origin)->unk_25,
                            actor->facing);
    if ((check_entity_interaction_compatibility(actor, initial_target) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & 0x8000) &&
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

    action_state->action_phase = 0;
    ((T_80173734_S_80173734_3 *)action_state)->unk_8C = 0;
    action_state->action_id = 0x11;

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
                          ((T_80173734_S_80173734_2 *)origin)->unk_25, actor->facing, 10);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AC = 0;
        if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
            {
                s16 target_distance = get_tile_chebyshev_distance(
                    ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                prepare_directional_attack(actor, origin, actor->facing, target_distance,
                              ((T_80173734_S_80173734_0 *)actor)->unk_60);
            }

            if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                range_left = 10;
                origin_x = ((T_80173734_S_80173734_2 *)origin)->unk_24;
                origin_y = ((T_80173734_S_80173734_2 *)origin)->unk_25;

loop:
                next_x = ((T_80173734_S_80173734_0 *)actor)->unk_72;
                next_y = ((T_80173734_S_80173734_0 *)actor)->unk_73;
                resolve_attack_damage_and_effects(actor, origin, actor->facing,
                              ((T_80173734_S_80173734_3 *)action_state)->unk_AA);
                range_left -= ((T_80173734_S_80173734_3 *)action_state)->unk_AA;
                if (range_left != 0) {
                    ((T_80173734_S_80173734_2 *)origin)->unk_24 = next_x;
                    ((T_80173734_S_80173734_2 *)origin)->unk_25 = next_y;
                    ((T_80173734_S_80173734_0 *)actor)->unk_60 =
                        scan_actor_along_heading(actor, ((T_80173734_S_80173734_2 *)origin)->unk_24,
                                      ((T_80173734_S_80173734_2 *)origin)->unk_25,
                                      actor->facing, (s16)range_left);
                    if (((T_80173734_S_80173734_0 *)actor)->unk_60 != 0) {
                        ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                        ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
                        {
                            s16 target_distance = get_tile_chebyshev_distance(
                                ((T_80173734_S_80173734_4_pre *)(((T_80173734_S_80173734_0 *)actor)->unk_60))[-1].unk_00, origin);
                            ((T_80173734_S_80173734_3 *)action_state)->unk_AA = target_distance;
                            prepare_directional_attack(actor, origin, actor->facing, target_distance,
                                          ((T_80173734_S_80173734_0 *)actor)->unk_60);
                        }
                        if (((T_80173734_S_80173734_0 *)actor)->unk_14 & 0x04000000) {
                            goto loop;
                        }
                    } else {
                        prepare_directional_attack(actor, origin, actor->facing, 1, 0);
                        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
                    }
                }
                ((T_80173734_S_80173734_2 *)origin)->unk_24 = origin_x;
                ((T_80173734_S_80173734_2 *)origin)->unk_25 = origin_y;
            }
        } else {
            prepare_directional_attack(actor, origin, actor->facing, 1, 0);
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
        prepare_directional_attack(actor, origin, actor->facing, 1, 0);
        ((T_80173734_S_80173734_3 *)action_state)->unk_AA = 1;
    }

    return result;
}

/* Resolves action targets, updates the actor position, and sets the follow-up state. */
void prepare_actor_path_movement(ActorRecord *action_input, ObjectPosition *x_offset_input, SpriteFrameState *position_input, ActorRecord *actor_input) {
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
    action_input->action_id = 0x11;
    action_input->action_phase = 0;
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
