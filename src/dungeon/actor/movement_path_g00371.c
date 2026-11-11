#include "dungeon/level/room_flags.h"
#include "shared/actor_status_flags.h"
/* Movement path (G00371). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D38EC, CL:dungeon/func_800D3B60, CL:dungeon/func_800D40C0, PD:dungeon/engine:800E260C. */
#include "dungeon/actor.h"
#include "dungeon/actor/movement_path_g00371.h"
#include "dungeon/actor/state_ids.h"

#include "shared/tile_object.h"
#include "dungeon/item.h"
#include "dungeon/actor/state.h"
#include "shared/sprite_frame_state.h"/* Update entity callbacks, facing, movement, and floor contact. */
#include "dungeon/player/object.h"
void update_actor_movement_and_contact(S_func_800D8728_0 *entity, ObjectPosition *motion, SpriteFrameState *monster)
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
    monster->clut = 0;

    if (g_dungeon_status.flags & 0x2000) {
        Callback special_callback = entity->unk_8C;
        if (special_callback == (Callback)&actor_action_resume_address) {
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
    actor_contact_callbacks[entity->unk_9A](entity, motion, monster, entity);

    if ((s16)previous_direction != (s8)entity->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, monster, entity);
    }

    model_flags = monster->flags;
    if (!(model_flags & 0x8000)) {
        direction_sector = (g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100) >> 9;
        state_direction = direction_sector & 7;
        lookup_direction = state_direction;
        compare_direction = state_direction;
        if (entity->unk_94 != compare_direction) {
            void *direction_table = monster->frameTable;
            if (direction_table != 0) {
                s32 direction_offset = (s16)compare_direction * 4;
                select_record_entry_and_value(monster,
                              *(void **)(direction_offset + (long)direction_table),
                              monster->unk_04);
            }
            entity->unk_94 = state_direction;
        }

        if (dir_sprite_flag[lookup_direction] != 0) {
            monster->flags |= 1;
        } else {
            monster->flags &= 0xFFFE;
        }

        if (!(actor->unk_1C & ACTOR_PARALYZED)) {
            if (!(monster->flags & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            monster->flags |= 0x7000;
        }

        apply_monster_koyaw_data(actor->unk_1C, (u8 *)monster + 0xC);
    } else if (model_flags & 0x800) {
        monster->flags = model_flags & 0x8FFF;
    } else {
        monster->flags = model_flags | 0x7000;
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (entity->unk_9A == ACTOR_STATE_NO_OP) {
        s16 hop_timer;
        hop_timer = (s16)(--entity->unk_A0.u16);
        if (hop_timer == 2) {
            s32 hop_direction_offset;
            entity->unk_98 |= 1;
            monster->frameTable = actor_movement_frames;
            hop_direction_offset = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 7) & 0x1C;
            select_record_entry_and_value(monster, *(void **)(actor_movement_frames + hop_direction_offset), 0);
        }

        if (entity->unk_A0.s16 == 0) {
            motion->velocity_z = (s32)0xFFE00000;
        }

        if ((u16)(entity->unk_A0.u16 + 7) < 8) {
            motion->velocity_z += 0x40000;
        } else {
            motion->velocity_z = 0;
        }

        if (entity->unk_A0.s16 < -7) {
            entity->unk_98 &= 0xFFFE;
            entity->unk_A0.u16 = (rand() & 0x3F) | 0x40;
        }
    } else {
        entity->unk_98 &= 0xFFFE;
    }

    if (entity->unk_98 & 8) {
        entity->unk_9D = 0;
    } else {
        motion->velocity_z +=
            ((s8)entity->unk_9D * 5) << 14;
        entity->unk_9D++;
    }
    entity->unk_90.s32 += motion->velocity_z;

    if (!(entity->unk_98 & 4)) {
        floor_height = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                                     motion->y.unsigned_parts.integer,
                                     (s16)(actor->unk_88.u16 - 0x20));
        if (floor_height < 0x200) {
            if (entity->unk_90.half.unk_92.s16 + actor->unk_88.s16 < floor_height) {
                actor->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
            } else if (floor_height >= actor->unk_88.s16) {
                entity->unk_90.s32 = 0;
                motion->velocity_z = 0;
                actor->unk_1C |= ACTOR_GROUNDED;
                entity->unk_9D = 0;
            } else {
                motion->velocity_z = 0;
                actor->unk_1C |= ACTOR_GROUNDED;
                entity->unk_9D = 0;
                entity->unk_90.half.unk_92.u16 = floor_height - actor->unk_88.u16;
            }

            if (actor->unk_1C & ACTOR_REFRESH_GROUND) {
                actor->unk_1C &= ACTOR_REFRESH_GROUND_CLEAR_MASK;
                floor_height = sample_terrain_surface_height((monster->tile_x << 6) | 0x20,
                                             (monster->tile_y << 6) | 0x20,
                                             (s16)(actor->unk_88.u16 - 0x20));
                entity->unk_90.half.unk_92.u16 += actor->unk_88.u16 - floor_height;
                actor->unk_88.u16 = floor_height;
            }
        } else {
            actor->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
        }
    } else {
        actor->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
    }
    motion->z.unsigned_parts.integer =
        actor->unk_88.u16 + entity->unk_90.half.unk_92.u16;
    monster->flags |= 0x40;
}

/* Updates actor state, facing, and directional animation. */
void update_actor_facing_animation(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *status)
{
    void **anim_table;
    s32 cell_record;
    u16 direction_aux;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id = 0xE;
        advance_actor_queued_path(actor, motion, sprite, status);
        return;
    }

    if (status->mp_value.parts.whole == 0) {
        void *current_anim;

        advance_actor_pending_action(actor, motion, sprite, status);
        current_anim = sprite->frameTable;
        anim_table = actor_action_frames;
        if (current_anim == anim_table) {
            return;
        }
    } else {

        if (((u32)status->flags1C) & ACTOR_ASLEEP) {
            if (sprite->frameTable == actor_action_frames) {
                actor->action_id = 0xD;
                actor->action_phase = 1;
                actor->unk_8C.handler = NULL;
                status->flags1C &= ~0x40000;
                return;
            }
            if (reset_actor_action_state(actor, motion, sprite, 0)) {
                return;
            }
        }

        if (!(g_dungeon_status.flags & 0x2000)) {
            if (((u32)status->flags1C) & ACTOR_PUSH_PENDING) {
                begin_pushed_actor_move(actor, motion, sprite, status);
                return;
            }

            if (actor->action_id != 0xE) {
                u8 next_state = 0xE;

                anim_table = actor_action_frames;
                if (sprite->frameTable != anim_table) {
                    (*(void **)((u8 *)sprite + (0x2C))) = anim_table;
                    select_record_entry_and_value(sprite,
                        *(void **)((u8 *)anim_table +
                            (((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 7) & 0x1C)),
                        0);
                }
                actor->action_id = next_state;
            }

            actor->action_state_flags &= 0xFFF3;
            if (status->hp_delta != 0) {
                if (begin_ready_actor_directional_action(actor, motion, sprite, 0)) {
                    return;
                }
            }

            if (((u32)status->flags1C) & ACTOR_LIFTED) {
                actor->unk_90.value = 0;
                actor->action_state_flags &= 0xFFFE;
                motion->velocity_z = 0;
                /*
                 * BUG: Tumna leaves an already lifted familiar on Koh's tile. Restarting lift setup here
                 * clears Koh's occupancy; resume the attachment without clearing the tile.
                 * Found and documented by the Azure Dreams community
                 * (adrando.com/guide/bugs.html).
                 */
                begin_actor_move_to_target_facing(actor, motion, sprite, status);
                install_actor_action_handler_after_floor_trap_check(actor, motion, sprite, status);
                return;
            }

            if ((s16)can_entity_gain_level(status) != 0) {
                process_selected_actor_record(actor, motion, sprite, status);
            }
        }

        cell_record = find_active_rect_containing_point(sprite->tile_x,
            sprite->tile_y);
        sprite->room_index = cell_record;

        if (status->pending_turn_updates > 0) {
            if (((u32)status->flags1C) & ACTOR_PARALYZED) {
                update_actor_status_and_mp(status);
                return;
            }
            advance_actor_traversable_heading(actor, motion, sprite, status);
            return;
        }

        if (!(((u32)status->flags1C) & ACTOR_PLAYER_SIDE)) {
            s32 record_index = (s8)cell_record;

            if ((record_index < 0) ||
                !(dungeon_rooms[record_index].flags & ROOM_HOLY_BEAM)) {
                if (!(((u32)status->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                    if ((s16)test_neighbor_position_relation(sprite->tile_x,
                            sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                            reference_tile_object.tile_position.parts.tile_y) != 0) {
                        status->facing = get_rounded_facing_and_rounding_flag(
                            sprite->tile_x, sprite->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                            &direction_aux);
                    }
                }
            }
        }

        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
        if (sprite->flags & 0x40) {
            return;
        }
        anim_table = actor_action_frames;
        if (sprite->frameTable == anim_table) {
            return;
        }
        if (actor->action_state_flags & 1) {
            return;
        }
    }
    (*(void **)((u8 *)sprite + (0x2C))) = anim_table;
    select_record_entry_and_value(sprite,
        *(void **)((((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 7) & 0x1C) +
            (u32)anim_table),
        0);
}

/* Advance the actor along its queued path and update movement timing. */
void advance_actor_queued_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    ActorRecord *state = actor;
    void *anim_table;
    s32 tile_mask;
    s16 direction;
    s16 move_result;
    s16 old_x;
    s32 old_y;
    s32 step_count;

    if ((((s8)state->movement_queue_state) > 0) &&
        ((s32)state->movement_queue_state > state->unk_8A)) {
        anim_table = sprite->frameTable;
        if (anim_table != actor_movement_frames) {
            void *anim_slot;

            sprite->frameTable = actor_movement_frames;
            anim_slot = actor_movement_frames +
                (((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 7) & 0x1C);
            select_record_entry_and_value(sprite, *(void **)anim_slot, 0);
        } else if (sprite->flags & 0x6000) {
            select_record_entry_and_value(
                sprite,
                *(void **)(actor_movement_frames +
                    (((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 7) & 0x1C)),
                0);
        }

        old_x = sprite->tile_x;
        old_y = sprite->tile_y;
        tile_mask = 0x3000;
        if (state->flags1C & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

        direction = (s16)get_rounded_facing_and_rounding_flag(old_x, old_y,
                                  state->path_x[state->unk_8A],
                                  state->path_y[state->unk_8A],
                                  (u8 *)body + 0x98);
        move_result = (s16)check_movement_clearance_and_height(direction, sprite, state, 0x20);

        sprite->tile_x = state->path_x[state->unk_8A];
        tile_mask = 0x3000;
        sprite->tile_y = state->path_y[state->unk_8A];
        state->unk_8A = state->unk_8A + 1;

        {
            s32 new_x = sprite->tile_x;
            s32 new_y = sprite->tile_y;
            if (state->flags1C & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(new_x, new_y, tile_mask);
        }

        state->facing = direction;
        if ((move_result == 3) &&
            ((g_dungeon_status.flags & 0x80) || (sprite->flags & 0x8000))) {
            body->action_id = 0xF;
        } else {
            initialize_actor_direction_table(body, position, sprite, state);
        }
        body->unk_8C.word = 0;
        state->flags1C |= 0x40000000;
        if (g_dungeon_status.flags & 0x80) {
            body->action_timer = 0;
            return;
        }

        body->action_timer = 8;
        step_count = state->movement_queue_state;
        if (step_count > 0) {
            body->action_timer = 8 / step_count;
        }
    }
}

/* Advances an actor along a traversable heading and updates its movement state. */
void advance_actor_traversable_heading(ActorRecord *body, ObjectPosition *context, SpriteFrameState *position, ActorRecord *actor) {
    s32 tile_mask;
    s32 target_y;
    s32 target_x;
    s16 candidate_heading;
    s32 heading_delta;
    s16 target_heading;
    s16 direction_or_x;
    s32 next_y;
    s8 *room_cache;
    void * turn_flags;
    s32 flags_or_heading;
    s32 actor_flags;
    s32 movement_bits;
    s32 target_direction;
    s32 limit_turn;
    s8 room_id;
    s16 turn_index;
    u8 *turn_offsets;

    limit_turn = 0;
    if ((g_dungeon_status.flags & 0x4000) || ((s8)actor->movement_queue_state >= 0)) {
        update_actor_status_and_mp(actor);
        return;
    }
    if (g_dungeon_status.flags & 0x2000) {
        room_cache = ((void *)body) + 0x9C;
        update_actor_proximity_flag(position, actor, 3, 6, room_cache);
        flags_or_heading = actor->flags1C;
        movement_bits = flags_or_heading & 0x410;
        if (movement_bits) {
            movement_bits = flags_or_heading & 0x400;
            if (movement_bits) {
                s32 marked_flags = actor->flags14;
                if (marked_flags >= 0) {
                    flags_or_heading = 0x80000000;
                    marked_flags |= flags_or_heading;
                    actor->flags14 = marked_flags;
                    actor->facing = (actor->facing + ((generate_random_value() & 7) << 9));
                }
            }
            goto init_loop;
        }
        if (((s8)actor->movement_queue_state < 0) && (g_dungeon_status.flags & 0x2000)) {
            update_actor_proximity_flag(position, actor, 3, 6, room_cache);
            actor_flags = actor->flags1C;
            if (actor_flags & 0x2000) {
                if (actor_flags & 0x20000) {
                    {

                        target_direction = (actor->unk_44.bytes.high
                            + ((s32) (((S_800D92C0_1 *)(((int)primary_actor_record)))->unk_2A << 0x10) >> 0x19)) & 7;
                        target_x = D_80082E80_initial.tile_position.parts.tile_x + ((u16 *)dir_step_x)[target_direction];
                        target_y = D_80082E80_initial.tile_position.parts.tile_y + ((u16 *)dir_step_y)[target_direction];
                    }
                    if ((position->tile_x != (target_x & 0xFFFF))
                        || (position->tile_y != (target_y & 0xFFFF))) {
                        turn_flags = &body->action_state_flags;
                        target_heading = get_rounded_facing_and_rounding_flag(position->tile_x, position->tile_y, (s16)target_x,
                            (s16)target_y, turn_flags);
                        actor->facing = target_heading;
                        if ((check_movement_clearance_and_height(target_heading, position, actor, 0x20) << 0x10) <= 0) {
                                                        actor->facing = get_rounded_facing_and_rounding_flag(position->tile_x,
                                position->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, turn_flags);
                        }
                        {
                                                        s32 distance_result;
                            distance_result = test_neighbor_position_relation(position->tile_x, position->tile_y,
                                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y);
                            if ((distance_result << 0x10) != 0) {
                                limit_turn = 1;
                            }
                            turn_index = 0;
                        }
                        goto loop_entry;
                    }
                    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
                    return;
                }
            } else {
                room_id = (s8)position->room_index;
                if ((room_id < 0) || !(dungeon_rooms[room_id].flags & ROOM_HOLY_BEAM)) {
                    if (actor->action_flags & 0x8000) {
                        goto init_loop;
                    }
                }
            }
            select_actor_route_target(position, body->unk_9C, (void *)actor, ((void *)body) + 0x98);
init_loop:
            turn_index = 0;
loop_entry:
            turn_offsets = (u8 *)actor_turn_angle_offsets;
try_heading:
            flags_or_heading = actor->facing;
            if (body->action_state_flags & 2) {
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
                    actor->facing = candidate_heading;
                    actor->path_x[(actor->movement_queue_state & 0x7F)] =
                        (u8) position->tile_x;
                    actor->path_y[(actor->movement_queue_state & 0x7F)] =
                        (u8) position->tile_y;
                    actor->movement_queue_state = actor->movement_queue_state + 1;
                    update_map_cell_flags_with_item_limit(position->tile_x, position->tile_y,
                                  (actor->flags1C & 0x2000) ? 0x300 : 0x3000);
                    direction_or_x = (actor->facing >> 8) & 0xE;
                    {
                        u8 *x_table_base = (u8 *)dir_step_x;
                        u8 next_x = position->tile_x;
                        next_x += x_table_base[direction_or_x];
                        position->tile_x = (u8) next_x;
                    }
                    position->tile_y = (u8) (position->tile_y + ((u8 *)dir_step_y)[direction_or_x]);
                    direction_or_x = position->tile_x;
                    next_y = position->tile_y;
                    tile_mask = 0x3000;
                    if (actor->flags1C & 0x2000) {
                        tile_mask = 0x300;
                    }
                    cycle_map_cell_flags(direction_or_x, next_y, tile_mask);
                    goto post_loop;
                }
            }
            if (turn_index == 0) {
                /* BYTES: retail compares the packed tile column/row pair as one halfword (lhu) against the reference tile word */
                if (reference_tile_object.tile_position.word == (*(u16 *)&position->tile_x)) {
                    if (++turn_index < 8) {
                        goto try_heading;
                    }
                    goto post_loop;
                }
                if ((check_entity_relation(actor, ((S_800D92C0_1 *)(((int)primary_actor_record)))->unk_58 + 0x20) << 0x10) != 0) {
                    /* BYTES: reorg mostly_true_jump: LOOP_BEG before the join label decides a delay-slot fill (ledger/onetrip_loadbearing.jsonl: dungeon/func_800D3B60). */
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
                    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
                    actor->action_flags = (u16) (actor->action_flags & 0x7FFF);
                    update_actor_status_and_mp(actor);
                    return;
                }
            }
            body->unk_9C = (s8) (u8) position->room_index;
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
            {
                g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
            }
            if (actor->pending_turn_updates == 0) {
mask_and_return:
                actor->movement_queue_state = actor->movement_queue_state & 0x7F;
                return;
            }

            turn_index = sample_terrain_surface_height((position->tile_x << 6) | 0x20, (position->tile_y << 6) | 0x20,
                (s16) (actor->ground_height - 0x20));
            if (turn_index < 0x200) {
                actor->ground_height = turn_index;
            }
        }
    }
}

/*
 * Sets action state 0x10, clears its substate, and selects movement frames from the actor heading
 * relative to the camera.
 */
void initialize_actor_direction_table(void *object, void *unusedContext, SpriteFrameState *tableTarget, ActorRecord *headingSource) {
    s32 tableByteOffset;

    *((u8 *)object + 0x9A) = 0x10;
    *((u8 *)object + 0x9B) = 0;
    tableTarget->frameTable = actor_movement_frames;
    tableByteOffset = ((g_game_work.view.camera_rotation.parts.viewAngle + headingSource->facing + 0x100) >> 7) & 0x1C;
    select_record_entry_and_value(tableTarget, *(void **)(actor_movement_frames + tableByteOffset), 0);
}
