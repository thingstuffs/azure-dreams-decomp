/* Movement path (G00371). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D38EC, CL:dungeon/func_800D3B60, CL:dungeon/func_800D40C0, PD:dungeon/engine:800E260C. */
#include "dungeon/actor/movement_path_g00371.h"

/* Update entity callbacks, facing, movement, and floor contact. */
void update_actor_movement_and_contact(S_func_800D8728_0 *entity, S_func_800D8728_1 *motion, S_func_800D8728_2 *monster)
{
    S_func_800D8728_0 *actor;
    s16 previous_direction;
    s32 direction_sector;
    s32 state_direction;
    s16 lookup_direction;
    s16 compare_direction;
    s16 floor_height;
    u16 model_flags;

    actor = entity;
    *(u16 *)((u8 *)monster + 0x12) = 0;

    if (g_dungeon_status.flags & 0x2000) {
        Callback special_callback = entity->unk_8C;
        if (special_callback == (Callback)&D_800D8C64) {
            special_callback(entity, motion, monster, entity);
            return;
        }
        entity->unk_71 &= 0x7F;
        return;
    }

    previous_direction = (s8)entity->unk_6D;
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    {
        Callback callback = entity->unk_8C;
        if (callback != 0) {
            callback(entity, motion, monster, entity);
        }
    }
    D_800E264C[entity->unk_9A](entity, motion, monster, entity);

    if ((s16)previous_direction != (s8)entity->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, monster, entity);
    }

    model_flags = monster->unk_14;
    if (!(model_flags & 0x8000)) {
        direction_sector = (g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100) >> 9;
        state_direction = direction_sector & 7;
        lookup_direction = state_direction;
        compare_direction = state_direction;
        if (entity->unk_94 != compare_direction) {
            void *direction_table = monster->unk_2C;
            if (direction_table != 0) {
                s32 direction_offset = (s16)compare_direction * 4;
                func_8003DB94(monster,
                              *(void **)(direction_offset + (s32)direction_table),
                              monster->unk_04);
            }
            entity->unk_94 = state_direction;
        }

        if (dir_sprite_flag[lookup_direction] != 0) {
            monster->unk_14 |= 1;
        } else {
            ((S_func_800D8728_2 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(actor->unk_1C & 0x20)) {
            if (!(((S_func_800D8728_2 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((S_func_800D8728_2 *)monster)->unk_14 |= 0x7000;
        }

        apply_monster_koyaw_data(actor->unk_1C, (u8 *)monster + 0xC);
    } else if (model_flags & 0x800) {
        monster->unk_14 = model_flags & 0x8FFF;
    } else {
        monster->unk_14 = model_flags | 0x7000;
    }

    motion->unk_00.s32 += motion->unk_0C;
    motion->unk_04.s32 += motion->unk_10;

    if (entity->unk_9A == 14) {
        s16 hop_timer;
        hop_timer = (s16)(--entity->unk_A0.u16);
        if (hop_timer == 2) {
            s32 hop_direction_offset;
            entity->unk_98 |= 1;
            *(u8 **)((u8 *)monster + 0x2C) = D_800E260C;
            hop_direction_offset = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 7) & 0x1C;
            func_8003DB94(monster, *(void **)(D_800E260C + hop_direction_offset), 0);
        }

        if (entity->unk_A0.s16 == 0) {
            motion->unk_14 = (s32)0xFFE00000;
        }

        if ((u16)(entity->unk_A0.u16 + 7) < 8) {
            motion->unk_14 += 0x40000;
        } else {
            motion->unk_14 = 0;
        }

        if (entity->unk_A0.s16 < -7) {
            entity->unk_98 &= 0xFFFE;
            entity->unk_A0.u16 = (func_80069EF8() & 0x3F) | 0x40;
        }
    } else {
        entity->unk_98 &= 0xFFFE;
    }

    if (entity->unk_98 & 8) {
        entity->unk_9D = 0;
    } else {
        motion->unk_14 +=
            ((s8)entity->unk_9D * 5) << 14;
        entity->unk_9D++;
    }
    entity->unk_90.s32 += motion->unk_14;

    if (!(entity->unk_98 & 4)) {
        floor_height = sample_terrain_surface_height(motion->unk_00.half.unk_02,
                                     motion->unk_04.half.unk_06,
                                     (s16)(actor->unk_88.u16 - 0x20));
        if (floor_height < 0x200) {
            if (entity->unk_90.half.unk_92.s16 + actor->unk_88.s16 < floor_height) {
                actor->unk_1C &= 0xF7FFFFFF;
            } else if (floor_height >= actor->unk_88.s16) {
                entity->unk_90.s32 = 0;
                motion->unk_14 = 0;
                actor->unk_1C |= 0x08000000;
                entity->unk_9D = 0;
            } else {
                motion->unk_14 = 0;
                actor->unk_1C |= 0x08000000;
                entity->unk_9D = 0;
                entity->unk_90.half.unk_92.u16 = floor_height - actor->unk_88.u16;
            }

            if (actor->unk_1C & 0x40000000) {
                actor->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((monster->unk_24 << 6) | 0x20,
                                             (monster->unk_25 << 6) | 0x20,
                                             (s16)(actor->unk_88.u16 - 0x20));
                entity->unk_90.half.unk_92.u16 += actor->unk_88.u16 - floor_height;
                actor->unk_88.u16 = floor_height;
            }
        } else {
            actor->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        actor->unk_1C &= 0xF7FFFFFF;
    }
    motion->unk_0A =
        actor->unk_88.u16 + entity->unk_90.half.unk_92.u16;
    monster->unk_14 |= 0x40;
}

/* Updates actor state, facing, and directional animation. */
void update_actor_facing_animation(void *actor, EntityRec *motion, void *sprite, ActorRecord *status)
{
    void **anim_table;
    s32 cell_record;
    s32 direction_aux;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        advance_actor_queued_path(actor, motion, sprite, status);
        return;
    }

    if (status->mp == 0) {
        void *current_anim;

        advance_actor_pending_action(actor, motion, sprite, status);
        current_anim = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
        anim_table = D_800E262C;
        if (current_anim == anim_table) {
            return;
        }
    } else {

        if (((u32)status->flags1C) & 0x200) {
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == D_800E262C) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                status->flags1C &= ~0x40000;
                return;
            }
            if (reset_actor_action_state(actor, motion, sprite, 0)) {
                return;
            }
        }

        if (!(g_dungeon_status.flags & 0x2000)) {
            if (((u32)status->flags1C) & 0x100) {
                begin_pushed_actor_move(actor, motion, sprite, status);
                return;
            }

            if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                u8 next_state = 0xE;

                anim_table = D_800E262C;
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv != anim_table) {
                    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                    func_8003DB94(sprite,
                        *(void **)((u8 *)anim_table +
                            (((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 7) & 0x1C)),
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
            }

            ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
            if (status->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor, motion, sprite, 0)) {
                    return;
                }
            }

            if (((u32)status->flags1C) & 0x80000) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_90.at00_s32.v = 0;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFFE;
                motion->flags14 = 0;
                begin_actor_move_to_target_facing(actor, motion, sprite, status);
                install_actor_action_handler_after_floor_trap_check(actor, motion, sprite, status);
                return;
            }

            if ((s16)can_entity_gain_level(status) != 0) {
                process_selected_actor_record(actor, motion, sprite, status);
            }
        }

        cell_record = find_active_rect_containing_point(((Rec_func_800AA258_arg2 *)sprite)->unk_24,
            ((Rec_func_800AA258_arg2 *)sprite)->unk_25);
        ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_u8 = cell_record;

        if (status->pending_turn_updates > 0) {
            if (((u32)status->flags1C) & 0x20) {
                update_actor_status_and_food(status);
                return;
            }
            advance_actor_traversable_heading(actor, motion, sprite, status);
            return;
        }

        if (!(((u32)status->flags1C) & 0x2000)) {
            s32 record_index = (s8)cell_record;

            if ((record_index < 0) ||
                !(D_800E2970[record_index].flags & 2)) {
                if (!(((u32)status->flags1C) & 0x430)) {

                    if ((s16)compare_monster_neighbor_values(((Rec_func_800AA258_arg2 *)sprite)->unk_24,
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_25, D_80082E80.tile_position.parts.tile_x,
                            D_80082E80.tile_position.parts.tile_y) != 0) {
                        status->facing = get_rounded_facing_and_rounding_flag(
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_24, ((Rec_func_800AA258_arg2 *)sprite)->unk_25,
                            D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                            &direction_aux);
                    }
                }
            }
        }

        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x40) {
            return;
        }
        anim_table = D_800E262C;
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == anim_table) {
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 1) {
            return;
        }
    }
    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
    func_8003DB94(sprite,
        *(void **)((((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 7) & 0x1C) +
            (u32)anim_table),
        0);
}

/* Advance the actor along its queued path and update movement timing. */
void advance_actor_queued_path(void *action, s32 action_id, void *actor, void *move_state)
{
    void *state = move_state;
    void *anim_table;
    s32 tile_mask;
    s16 direction;
    s16 move_result;
    s16 old_x;
    s32 old_y;
    s32 step_count;
    void *step;

    if ((((S_800D904C_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_800D904C_0 *)state)->unk_71.u > ((S_800D904C_0 *)state)->unk_8A)) {
        anim_table = ((Rec_D_80082E80 *)actor)->unk_2C.as_pv;
        if (anim_table != D_800E260C) {
            void *anim_slot;

            (*(void * *)((u8 *)actor + (0x2C))) = D_800E260C;
            anim_slot = D_800E260C +
                (((g_game_work.view.camera_rotation.parts.viewAngle + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C);
            func_8003DB94(actor, *(void **)anim_slot, 0);
        } else if (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x6000) {
            func_8003DB94(
                actor,
                *(void **)(D_800E260C +
                    (((g_game_work.view.camera_rotation.parts.viewAngle + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C)),
                0);
        }

        old_x = ((Rec_D_80082E80 *)actor)->unk_24;
        old_y = ((Rec_D_80082E80 *)actor)->unk_25;
        tile_mask = 0x3000;
        if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

        step = (u8 *)state + ((S_800D904C_0 *)state)->unk_8A;
        direction = (s16)get_rounded_facing_and_rounding_flag(old_x, old_y,
                                  ((ActorStatusBytesView *)step)->unk_74,
                                  ((ActorStatusBytesView *)step)->unk_7C,
                                  (u8 *)action + 0x98);
        move_result = (s16)check_movement_clearance_and_height(direction, actor, state, 0x20);

        ((Rec_D_80082E80 *)actor)->unk_24 =
            ((ActorStatusBytesView *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_74;
        tile_mask = 0x3000;
        ((Rec_D_80082E80 *)actor)->unk_25 =
            ((ActorStatusBytesView *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_7C;
        ((S_800D904C_0 *)state)->unk_8A = (u16)((S_800D904C_0 *)state)->unk_8A + 1;

        {
            s32 new_x = ((Rec_D_80082E80 *)actor)->unk_24;
            s32 new_y = ((Rec_D_80082E80 *)actor)->unk_25;
            if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(new_x, new_y, tile_mask);
        }

        ((S_800D904C_0 *)state)->unk_2A = direction;
        if ((move_result == 3) &&
            ((g_dungeon_status.flags & 0x80) || (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000))) {
            ((S_800D904C_3 *)action)->unk_9A = 0xF;
        } else {
            initialize_actor_direction_table(action, action_id, actor, state);
        }
        ((S_800D904C_3 *)action)->unk_8C = 0;
        (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
        if (g_dungeon_status.flags & 0x80) {
            ((S_800D904C_3 *)action)->unk_96 = 0;
            return;
        }

        ((S_800D904C_3 *)action)->unk_96 = 8;
        step_count = ((S_800D904C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((S_800D904C_3 *)action)->unk_96 = 8 / step_count;
        }
    }
}

/* Advances an actor along a traversable heading and updates its movement state. */
void advance_actor_traversable_heading(void *move_state, void *context, S_800D92C0_2 *position, void *actor) {
    s32 tile_mask;
    s32 target_y;
    s32 target_x;
    s16 candidate_heading;
    s32 heading_delta;
    s16 target_heading;
    s16 direction_or_x;
    s32 next_y;
    s32 room_cache;
    s32 turn_flags;
    s32 flags_or_heading;
    s32 actor_flags;
    s32 movement_bits;
    s32 target_direction;
    s32 limit_turn;
    s8 room_id;
    s16 turn_index;
    u8 *turn_offsets;

    limit_turn = 0;
    if ((g_dungeon_status.flags & 0x4000) || (((S_800D92C0_0 *)actor)->unk_71 >= 0)) {
        update_actor_status_and_food(actor);
        return;
    }
    if (g_dungeon_status.flags & 0x2000) {
        room_cache = move_state + 0x9C;
        update_actor_proximity_flag(position, actor, 3, 6, room_cache);
        flags_or_heading = ((S_800D92C0_0 *)actor)->unk_1C;
        movement_bits = flags_or_heading & 0x410;
        if (movement_bits) {
            movement_bits = flags_or_heading & 0x400;
            if (movement_bits) {
                s32 marked_flags = ((S_800D92C0_0 *)actor)->unk_14;
                if (marked_flags >= 0) {
                    flags_or_heading = 0x80000000;
                    marked_flags |= flags_or_heading;
                    ((S_800D92C0_0 *)actor)->unk_14 = marked_flags;
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16)(((S_800D92C0_0 *)actor)->unk_2A.u + ((generate_random_value() & 7) << 9));
                }
            }
            goto init_loop;
        }
        if ((((S_800D92C0_0 *)actor)->unk_71 < 0) && (g_dungeon_status.flags & 0x2000)) {
            update_actor_proximity_flag(position, actor, 3, 6, room_cache);
            actor_flags = ((S_800D92C0_0 *)actor)->unk_1C;
            if (actor_flags & 0x2000) {
                if (actor_flags & 0x20000) {
                    {

                        target_direction = (((S_800D92C0_0 *)actor)->unk_45
                            + ((s32) (((S_800D92C0_1 *)(((int)D_800814A8)))->unk_2A << 0x10) >> 0x19)) & 7;
                        target_x = D_80082E80_initial.tile_position.parts.tile_x + ((u16 *)dir_step_x)[target_direction];
                        target_y = D_80082E80_initial.tile_position.parts.tile_y + ((u16 *)dir_step_y)[target_direction];
                    }
                    if ((position->unk_24.at00.v != (target_x & 0xFFFF))
                        || (position->unk_24.at01.v != (target_y & 0xFFFF))) {
                        turn_flags = move_state + 0x98;
                        target_heading = get_rounded_facing_and_rounding_flag(position->unk_24.at00u.v & 0xFF, position->unk_24.at01.v, (s16)target_x,
                            (s16)target_y, turn_flags);
                        ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) target_heading;
                        if ((check_movement_clearance_and_height(target_heading, position, actor, 0x20) << 0x10) <= 0) {
                                                        ((S_800D92C0_0 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(position->unk_24.at00.v,
                                position->unk_24.at01.v, D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, turn_flags);
                        }
                        {
                                                        s32 distance_result;
                            distance_result = compare_monster_neighbor_values(position->unk_24.at00.v, position->unk_24.at01.v,
                                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y);
                            if ((distance_result << 0x10) != 0) {
                                limit_turn = 1;
                            }
                            turn_index = 0;
                        }
                        goto loop_entry;
                    }
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                    return;
                }
            } else {
                room_id = position->unk_26;
                if ((room_id < 0) || !(D_800E2970[room_id].flags & 2)) {
                    if (((S_800D92C0_0 *)actor)->unk_46 & 0x8000) {
                        goto init_loop;
                    }
                }
            }
            rebuild_monster_reachable_tiles(position, ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8, actor, move_state + 0x98);
init_loop:
            turn_index = 0;
loop_entry:
            turn_offsets = (u8 *)D_8006CD00;
try_heading:
            flags_or_heading = ((S_800D92C0_0 *)actor)->unk_2A.s;
            if (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 2) {
                heading_delta = ((s16 *)turn_offsets)[turn_index];
                candidate_heading = flags_or_heading - heading_delta;
            } else {
                heading_delta = ((s16 *)turn_offsets)[turn_index];
                candidate_heading = flags_or_heading + heading_delta;
            }
            if ((check_movement_clearance_and_height((s16)candidate_heading, position, actor, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    s16 checked_limit = limit_turn;
                    if (checked_limit != 0) {
                        goto mask_and_return;
                    }
                }
                {
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) candidate_heading;
                    ((ActorStatusBytesView *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_74 =
                        (u8) position->unk_24.at00.v;
                    ((ActorStatusBytesView *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_7C =
                        (u8) position->unk_24.at01.v;
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 + 1);
                    update_map_cell_flags_with_item_limit(position->unk_24.at00.v, position->unk_24.at01.v,
                                  (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    direction_or_x = ((u16) ((S_800D92C0_0 *)actor)->unk_2A.u >> 8) & 0xE;
                    {
                        u8 *x_table_base = (u8 *)dir_step_x;
                        u8 next_x = position->unk_24.at00.v;
                        next_x += x_table_base[direction_or_x];
                        position->unk_24.at00.v = (u8) next_x;
                    }
                    position->unk_24.at01.v = (u8) (position->unk_24.at01.v + ((u8 *)dir_step_y)[direction_or_x]);
                    direction_or_x = position->unk_24.at00.v;
                    next_y = position->unk_24.at01.v;
                    tile_mask = 0x3000;
                    if (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) {
                        tile_mask = 0x300;
                    }
                    cycle_map_cell_flags(direction_or_x, next_y, tile_mask);
                    goto post_loop;
                }
            }
            if (turn_index == 0) {
                if (*(u16 *)(&D_80082E80.tile_position.parts.tile_x) == position->unk_24.at00u.v) {
                    if (++turn_index < 8) {
                        goto try_heading;
                    }
                    goto post_loop;
                }
                if ((check_entity_relation(actor, ((S_800D92C0_1 *)(((int)D_800814A8)))->unk_58 + 0x20) << 0x10) != 0) {
                    do {
                        return;
                    } while (0);
                }
            }
            if (++turn_index < 8) {
                goto try_heading;
            }

post_loop:
            {
                s32 post_index = turn_index;
                if (post_index >= 8) {
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                    ((S_800D92C0_0 *)actor)->unk_46 = (u16) (((S_800D92C0_0 *)actor)->unk_46 & 0x7FFF);
                    update_actor_status_and_food(actor);
                    return;
                }
            }
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8 = (s8) (u8) position->unk_26;
            ((S_800D92C0_0 *)actor)->unk_6D.u = (u8) (((S_800D92C0_0 *)actor)->unk_6D.u - 1);
            {
                g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
            }
            if (((S_800D92C0_0 *)actor)->unk_6D.s == 0) {
mask_and_return:
                ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                return;
            }

            turn_index = sample_terrain_surface_height((position->unk_24.at00.v << 6) | 0x20, (position->unk_24.at01.v << 6) | 0x20,
                (s16) (((S_800D92C0_0 *)actor)->unk_88 - 0x20));
            if (turn_index < 0x200) {
                ((S_800D92C0_0 *)actor)->unk_88 = (u16) turn_index;
            }
        }
    }
}

void initialize_actor_direction_table(void *object, void *unusedContext, void *tableTarget, void *headingSource) {
    s32 tableByteOffset;

    *((u8 *)object + 0x9A) = 0x10;
    *((u8 *)object + 0x9B) = 0;
    ((SpriteFrameState *)tableTarget)->frameTable = D_800E260C;
    tableByteOffset = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)headingSource + 0x2A) + 0x100) >> 7) & 0x1C;
    func_8003DB94(tableTarget, *(s32 *)(D_800E260C + tableByteOffset), 0);
}
