#include "engine/node/registration.h"
#include "shared/entity.h"
#include "shared/audio_commands.h"
/* Actor-targeted effect movement, rotating particles, and target lift and spin animation. */
#include "shared/object_node.h"
#include "dungeon/effect/motion/create_randomized_source_effect.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/motion/create_randomized_source_effect.h"
#include "dungeon/effect/motion.h"
#include "dungeon/system.h"

/* Moves an animated sprite outward along its saved angle with a fixed vertical step and removes it
   when animation ends. */
void move_sprite_in_radial_direction(RandomizedSourceEffectBody *motion, Row_8191C848_S_8191C848_3 *position, SpriteFrameState *status) {
    s32 y_step_scaled;
    Row_8191C848_S_8191C848_1 *counter_state;
    counter_state = motion->source_context;
    counter_state->unk_14 = (u16) (counter_state->unk_14 + 1);
    advance_sprite_animation_and_textures(status);
    if (status->flags & 0x6000) {
        ((Row_8191C848_S_8191C848_0_pre *)motion)[-1].unk_00 = (u16) (((Row_8191C848_S_8191C848_0_pre *)motion)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
    position->unk_02 = (u16) (position->unk_02 + ((s32) ((rsin(motion->heading)
        >> 4) * motion->radius) >> 8));
    y_step_scaled = (rcos(motion->heading) >> 4) * motion->radius;
    position->unk_0A = (u16) (position->unk_0A - 4);
    position->unk_06 = (u16) (position->unk_06 + (y_step_scaled >> 8));
}

/* Creates a yellow sprite with a random radial angle, copied source motion, and an overridden height. */
void *create_randomized_source_effect(Row_8191C938_S_8191C938_3 *source)
{
    s32 random_value;
    Row_8191C938_CopyBlock *object_block;
    RandomizedSourceEffectBody *state;
    SpriteFrameState *render_data;
    ObjectNodeHeader *object;
    Row_8191C938_CopyBlock *source_block;
    void *result;
    register u16 word_override;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = NODE_BODY(object);
        object->update_callback = D_80024048;
        state->source_context = source;
        state->unk_04 = 0;
        state->unk_06 = 6;
        random_value = rand();
        state->heading = random_value % 0x1000;
        state->radius = 0x10;
        render_data = object->sprite;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        render_data->color.c.b = 0;
        render_data->clut = 0x7DCF;
        render_data->flags |= 0xC;
        render_data->tpage_abr |= 0x20;
        render_data->flags |= 0x100;
        select_record_entry_and_value(render_data, homing_particle_sprite_entries, 0);
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        register_node(object, project_sprite_chain);
        object_block = *(Row_8191C938_CopyBlock * *)&object->position;
        source_block = source->unk_20;
        *object_block = *source_block;
        word_override = source->unk_16;
        result = object;
        ((Row_8191C938_S_8191C938_4 *)object_block)->unk_0A = word_override;
        return result;
    }
    result = NULL;
    return result;
}

/* Rotates a sprite through timed movement, a pause, and accelerating vertical motion before removal. */
void advance_timed_effect_motion(ScaledRotatingEffectBody *object, Row_8191CA88_S_8191CA88_3 *motion, Row_8191CA88_S_8191CA88_2 *effect) {
    s32 state;
    u16 state_unsigned;
    s32 timer;
    u16 old_timer;
    s32 move_timer;
    s32 move_duration;
    s32 moving;
    s32 signed_timer;
    s32 wait_duration;
    s32 waiting;
    Row_8191CA88_S_8191CA88_4 *global_base;
    s32 x_position;
    s32 x_velocity;
    s16 next_state;
    s32 y_velocity;
    s32 z_velocity;
    u16 phase;
    Row_8191CA88_S_8191CA88_1 *inner;

    inner = object->context;
    inner->unk_14 = inner->unk_14 + 1;
    phase = effect->unk_1A;
    effect->unk_1A = phase + 0x300;
    old_timer = object->unk_10;
    state = (s16)object->unk_0E;
    state_unsigned = object->unk_0E;
    timer = old_timer + 1;
    object->unk_10 = timer;

    switch (state) {
    case 0:
        x_position = motion->unk_00;
        x_velocity = motion->unk_0C;
        y_velocity = motion->unk_10;
        z_velocity = motion->unk_14;
        motion->unk_00 = x_position + x_velocity;
        motion->unk_04 += y_velocity;
        motion->unk_08 += z_velocity;
        move_timer = (s16)object->unk_10;
        move_duration = object->unk_14;
        if (move_timer < move_duration)
            return;
        next_state = object->unk_0E + 1;
        object->unk_10 = 0;
        object->unk_0E = next_state;
        return;

    case 1:
        signed_timer = timer << 16;
        wait_duration = object->unk_16;
        signed_timer >>= 16;
        waiting = signed_timer < wait_duration;
        if (waiting != 0) {
            return;
        }
        object->unk_0E = state_unsigned + 1;
        object->unk_10 = 0;
        return;

    case 2:
        motion->unk_08 -= timer << 16;
        if ((s16)object->unk_10 < 0x18) {
            return;
        }
        next_state = object->unk_0E + 1;
        object->unk_10 = 0;
        object->unk_0E = next_state;
        return;

    case 3:
        ((Row_8191CA88_S_8191CA88_0_pre *)object)[-1].unk_00 |= 0x8000;
        global_base = (Row_8191CA88_S_8191CA88_4 *)0x80080000;
        global_base->unk_14A0 |= 0x8000;

        return;
    default:
        return;
    }
}

/* Creates a rotating sprite with size and timing from the source, copies its motion, and adjusts
   vertical velocity. */
void * create_scaled_rotating_effect(void *params_input, void *transform_input) {
    Row_8191CBCC_S_8191CBCC_2 *params = params_input;
    Blk24 *source_transform = transform_input;
    s16 depth_scale;
    s32 size_fixed;
    s32 variant_random;
    s32 angle_random;
    s32 adjusted_depth;
    s32 angle;
    SpriteFrameState *render;
    ScaledRotatingEffectBody *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = NODE_BODY(object);
        object->update_callback = &D_80024288;
        state->context = params;
        state->unk_0E = 0;
        state->unk_10 = 0;
        variant_random = rand();
        state->unk_12 = (s16)(variant_random % 7);
        state->unk_14 = (u16) params->unk_12;
        state->unk_16 = (s16) (0x1C - params->unk_10);
        render = object->sprite;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->source = &D_80024F74;
        render->flags = (u16) (render->flags | 0xC);
        render->tpage_abr = (u16) (render->tpage_abr | 0x60);
        angle = rand();
        angle_random = angle;
        angle >>= 0xC;
        if (angle_random < 0) {
            angle = (s32) (angle_random + 0xFFF) >> 0xC;
        }
        angle = angle_random - (angle << 0xC);
        render->angle_z = (s16)angle;
        size_fixed = params->unk_10 << 8;
        render->scale_y = size_fixed;
        render->scale_x = size_fixed;
        register_node(object, &clipped_sprite_renderer_address);
        {
            ObjectPosition *transform;

            transform = object->position;
            *(Blk24 *) transform = *source_transform;
            depth_scale = state->unk_14;
            adjusted_depth = ((transform->velocity_z * depth_scale) -
                              (params->unk_10 << 0x13)) / depth_scale;
            transform->velocity_z = adjusted_depth;
            return object;
        }
    }
    return 0;
}

/* Moves an effect to its target, spins and lifts the target, restores its pose, and applies the attack. */
void update_actor_effect_sequence(Row_8191CD78_S_func_80024578_1 *effect, Row_8191CD78_S_func_80024578_2 *position, void *render_data)
{
    register Row_8191CD78_S_func_80024578_3 *actor;
    register Row_8191CD78_S_func_80024578_4 *render = render_data;
    register Row_8191CD78_S_func_80024578_5 *work_base;
    SpriteFrameState *motion_data;
    SpriteFrameState *map_data;
    Row_8191CD78_S_func_80024578_7 *origin_pos;
    void *target;
    s32 state;
    u16 frame;
    s32 index;
    s32 delta_x;
    s32 abs_delta_x;
    s32 abs_delta_x_2;
    s32 delta_y;
    s32 delta_z;
    u16 copied_z;

    s32 x_base;
    register s32 y_base;
    u8 scratch[32];
    u16 last_tile_y;
    s16 travel_frames;
    s16 *delta_cursor;
    u32 page_base;
    s16 final_floor;
    s32 expanded_floor;
    SpriteFrameState *finished_render;

    frame = effect->timer;
    state = (s16)effect->phase;
    actor = effect->caster;
    effect->timer = frame + 1;
    switch (state) {
    case 0:
        effect->timer = 0;
        effect->phase++;
        effect->direction = (u16)((actor->facing >> 9) & 7);
        render->color = 0x808080;
    case 1:
        work_base = (Row_8191CD78_S_func_80024578_5 *)((u8 *)actor - 0x20);
        motion_data = work_base->unk_0C;
        if (resolve_record_orientation_or_fallback(motion_data->source, motion_data, (scratch + 0x18), 0) == 0) {
            if ((work_base->unk_0C->flags & 0x8000) == 0) {
                break;
            }
        }
        origin_pos = work_base->unk_08.ptr;
        position->x.parts_02.unk_02 = origin_pos->x;
        position->y.parts_06.unk_06 = origin_pos->y;
        copied_z = origin_pos->z;
        position->z.parts_0A.unk_0A = copied_z;
        {
            u16 next_z;

            if ((work_base->unk_0C->flags & 0x8000) == 0) {
                position->x.parts_02.unk_02 = position->x.parts_02.unk_02 + DELTA(0);
                position->y.parts_06.unk_06 = position->y.parts_06.unk_06 + DELTA(1);
                {
                    u16 position_z;
                    s32 offset_z;

                    position_z = position->z.parts_0A.unk_0A;
                    offset_z = (u16)DELTA(2);
                    next_z = (u16)(position_z + offset_z);
                }
                position->z.parts_0A.unk_0A = next_z;
            } else {
                next_z = (u16)(copied_z - 64);
                position->z.parts_0A.unk_0A = next_z;
            }
        }
        if ((((Row_8191CD78_S_func_80024578_8 *)(effect->launch_flags))->flags & 0x80) == 0) {
            break;
        }
        target = actor->target;
        index = 1;
        if (target != 0) {
            work_base = ((Row_8191CD78_S_func_80024578_11 *)((u8 *)(actor->target) - 0x20))->position;
            effect->target_position = work_base;
            effect->target = actor->target;
            effect->target_sprite =
                ((Row_8191CD78_S_func_80024578_11 *)((u8 *)(actor->target) - 0x20))->sprite;
            effect->target_ground_height = ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->ground_height;
            effect->saved_facing = ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing;

            abs_delta_x = abs(((s16)work_base->unk_00.parts_02.unk_02) - ((s16)position->x.parts_02.unk_02));
            DELTA(0) = (s16)abs_delta_x;
            {
                s32 distance_y;
                s32 position_y;
                distance_y = (s16)work_base->unk_04.parts_06.unk_06;
                position_y = (s16)position->y.parts_06.unk_06;
                distance_y -= position_y;
                distance_y = abs(distance_y);
                DELTA(1) = (s16)distance_y;
            }
            {
                s32 distance_z;
                s32 position_z;
                position_z = (s16)position->z.parts_0A.unk_0A;
                distance_z = ((Row_8191CD78_S_func_80024578_3 *)(actor->target))->ground_height;

                delta_cursor = (s16 *)(scratch + 2);
                distance_z -= position_z;
                distance_z = abs(distance_z);
                DELTA(2) = (s16)distance_z;
            }
            effect->unk_12 = DELTA(0);
            index = 1;
            do {
                {
                    if (((Row_8191CD78_S_func_80024578_9 *)(delta_cursor))->unk_18 > effect->unk_12) {
                        effect->unk_12 = (u16)((Row_8191CD78_S_func_80024578_9 *)(delta_cursor))->unk_18;
                    }
                    index++;
                    delta_cursor++;
                }
            } while (index < 3);
            travel_frames = (s16)(((u16)effect->unk_12 << 16) >> 20);
            effect->unk_12 = travel_frames;
            if (travel_frames == 0) {
                effect->unk_12 = 1;
            }
            position->velocity_x =
                (work_base->unk_00.s32 - position->x.s32) / effect->unk_12;
            position->velocity_y =
                (work_base->unk_04.s32 - position->y.s32) / effect->unk_12;
            position->velocity_z =
                (((s32)((Row_8191CD78_S_func_80024578_3 *)(actor->target))->ground_height << 16) -
                 position->z.s32) / effect->unk_12;
            effect->phase++;
        } else {
            index = 0;
            map_data = work_base->unk_0C;
            page_base = 0x80070000;
            {
                u16 tile_x;
                s32 tile_y;
                u16 last_tile_x;
                u16 tile_y_bits;
                s32 floor_x;
                s32 floor_limit;
                s32 floor_y;
                s32 signed_tile_x;
                s32 signed_tile_y;
                s32 x_adjust;
                s32 y_adjust;
                s16 *x_adjust_table;

                tile_y = map_data->tile_y;
                tile_x = map_data->tile_x;
                last_tile_y = (u16)tile_y;
                last_tile_x = tile_x;
                do {
                    signed_tile_x = (s16)tile_x;
                    signed_tile_y = (s16)tile_y;
                    if ((check_layer_offset_height((signed_tile_x << 6) & 0xFFC0, (signed_tile_y << 6) & 0xFFC0,
                                       actor->ground_height,
                                       (s16)(effect->direction << 9)) << 16) == 0) {
                        s16 floor = sample_terrain_surface_height(
                            ((signed_tile_x + ((s16 *)((u8 *)dir_step_x))[(s16)effect->direction]) << 6) + 0x20 & 0xFFE0,
                            ((signed_tile_y + ((s16 *)((u8 *)dir_step_y))[(s16)effect->direction]) << 6) + 0x20 & 0xFFE0,
                            (s16)(actor->ground_height - 0x20));
                        if ((floor < 513) && ((s16)(floor - actor->ground_height) >= -63)) {
                            u16 next_tile_x;
                            s32 next_tile_y;

                            index++;
                            next_tile_x = tile_x + ((u16 *)((u8 *)dir_step_x))[(s16)effect->direction];
                            tile_x = next_tile_x;
                            next_tile_y = tile_y + ((u16 *)((u8 *)dir_step_y))[(s16)effect->direction];
                            last_tile_y = (u16)next_tile_y;
                            tile_y = next_tile_y;
                            last_tile_x = next_tile_x;
                            if (index < 8) {
                                continue;
                            }
                        }
                    }
                    break;
                } while (index < 8);

                work_base = (Row_8191CD78_S_func_80024578_5 *)scratch;
                x_base = (last_tile_x << 16) >> 10;
                floor_x = (x_base + 0x20);
                floor_x &= 0xFFE0;
                x_adjust_table = (s16 *)((u8 *)dir_step_x);
                floor_limit = -0x400;

                tile_y_bits = last_tile_y;
                y_base = (s32)tile_y_bits << 16;
                y_base >>= 10;
                floor_y = y_base + 0x20;
                x_adjust = x_adjust_table[(s16)effect->direction];
                work_base->unk_00.parts_02.unk_02 = (u16)(x_base + ((x_adjust + 1) << 5));
                y_adjust = ((s16 *)((u8 *)dir_step_y))[(s16)effect->direction];
                floor_y &= 0xFFE0;
                work_base->unk_04.parts_06.unk_06 = (u16)(y_base + ((y_adjust + 1) << 5));
                final_floor = sample_terrain_surface_height(floor_x, floor_y, floor_limit);
                index = 1;
                {
                    s32 widened_y;
                    s32 position_y;
                    s16 *delta_scan = (s16 *)(scratch + 2);

                    work_base->unk_08.parts_0A.unk_0A = final_floor;
                    expanded_floor = (s32)final_floor << 16;
                    abs_delta_x_2 = abs((s16)work_base->unk_00.parts_02.unk_02 - (s16)position->x.parts_02.unk_02);
                    DELTA(0) = (s16)abs_delta_x_2;
                    widened_y = work_base->unk_04.parts_06.unk_06;
                    position_y = (s16)position->y.parts_06.unk_06;
                    widened_y <<= 16;
                    widened_y >>= 16;
                    widened_y -= position_y;
                    widened_y = abs(widened_y);
                    DELTA(1) = (s16)widened_y;
                    expanded_floor >>= 16;
                    expanded_floor -= (s16)position->z.parts_0A.unk_0A;
                    DELTA(2) = (s16)(abs(expanded_floor));
                    effect->unk_12 = DELTA(0);
                    do {
                        if (((Row_8191CD78_S_func_80024578_9 *)(delta_scan))->unk_18 > effect->unk_12) {
                            effect->unk_12 = ((Row_8191CD78_S_func_80024578_9 *)(delta_scan))->unk_18;
                        }
                        index++;
                        delta_scan++;
                    } while (index < 3);
                }
            }
            travel_frames = (s16)(((u16)effect->unk_12 << 16) >> 20);
            effect->unk_12 = travel_frames;
            if (travel_frames == 0) {
                effect->unk_12 = 1;
            }
            position->velocity_x =
                (work_base->unk_00.s32 - position->x.s32) / effect->unk_12;
            position->velocity_y =
                (work_base->unk_04.s32 - position->y.s32) / effect->unk_12;
            position->velocity_z =
                (work_base->unk_08.s32 - position->z.s32) / effect->unk_12;

            effect->phase = 11;
        }
        effect->timer = 0;

        create_scaled_rotating_effect(effect, position);
        break;

    case 3:
        position->x.s32 += position->velocity_x;
        position->y.s32 += position->velocity_y;
        position->z.s32 += position->velocity_z;
        if (effect->timer < effect->unk_12) {
            break;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        drain_audio_commands_and_service_channels();
        {
            Row_8191CD78_S_func_80024578_3 *owner = effect->target;
            s32 flags;

            effect->added_property_flag = 0;
            flags = owner->property_flags;
            if ((flags & 0x100000) == 0) {
                owner->property_flags = flags | 0x100000;
                effect->added_property_flag = 1;
            }
        }
        effect->phase++;
        effect->timer = 0;
        break;

    case 4:
        if (read_sound_mode_blocking_status(4) == 1) {
            effect->phase++;
            effect->timer = 0;
            break;
        }
        break;

    case 6:
        ((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.parts_0A.unk_0A =
            (u16)(((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.parts_0A.unk_0A - effect->timer);
        ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing =
            (u16)(((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing + 0x200);
        if (effect->timer >= 28) {
            finished_render = effect->target_sprite;

            state = finished_render->angle_z;
            state += 0x800;
            finished_render->angle_z = state;
            effect->phase++;
            effect->timer = 0;
            break;
        }
        break;

    case 7:
        ((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.parts_0A.unk_0A =
            (u16)(((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.parts_0A.unk_0A + effect->timer * 4);
        ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing =
            (u16)(((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing + 0x200);
        {
            u8 *height_base;
            Row_8191CD78_S_func_80024578_2 *target_pos;
            Row_8191CD78_S_func_80024578_10 *height_entry;
            u16 max_height;
            Row_8191CD78_S_func_80024578_3 *owner;
            s32 effect_size;

            height_base = entity_height_offsets;
            owner = effect->target;
            target_pos = effect->target_position;
            height_entry = (Row_8191CD78_S_func_80024578_10 *)(height_base + owner->species);
            effect_size = 16;
            if ((s16)target_pos->z.parts_0A.unk_0A >=
                (s16)effect->target_ground_height - height_entry->unk_00) {
                delta_x = 8;
                max_height = effect->target_ground_height;
                target_pos->z.parts_0A.unk_0A =
                    (u16)(max_height - height_entry->unk_00);
                initialize_timed_motion_step(delta_x, effect_size);
                index = 0;
                do {
                    create_randomized_source_effect(effect);
                    index++;
                } while (index < 8);
                effect->phase++;
                effect->timer = 0;
                break;
            }
        }
        break;

    case 8:
        ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing =
            (u16)(((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing + 0x200);
        index = 0;
        if (effect->timer == 2) {
            do {
                create_randomized_source_effect(effect);
                index++;
            } while (index < 8);
        }
        if (effect->timer < 12) {
            break;
        }
        effect->phase++;
        effect->timer = 0;
        break;

    case 9:
        if (effect->timer < 4) {
            break;
        }
        ((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.s32 = effect->saved_z;
        ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->facing = effect->saved_facing;
        if (effect->added_property_flag != 0) {
            ((Row_8191CD78_S_func_80024578_3 *)(effect->target))->property_flags &= 0xFFEFFFFF;
        }
        effect->target_sprite->angle_z -= 0x800;
        apply_attack_power_and_element_effects(actor->target, 24, effect->variant, 4,
                      (s16)(effect->direction << 9), actor, 1);
        effect->phase++;
        effect->timer = 0;
        break;

    case 10:
        if (effect->child_updates != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        ((Row_8191CD78_S_func_80024578_12 *)((u8 *)(effect) - 2))->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 2:
    case 11:
        create_scaled_rotating_effect(effect, position);
        if (effect->timer < 15) {
            break;
        }
        {
            s32 saved_height = ((Row_8191CD78_S_func_80024578_2 *)(effect->target_position))->z.s32;

            effect->phase++;
            effect->timer = 0;
            effect->saved_z = saved_height;
        }
        break;

    case 12:
        position->x.s32 += position->velocity_x;
        position->y.s32 += position->velocity_y;
        position->z.s32 += position->velocity_z;
        if (effect->timer < effect->unk_12) {
            break;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        drain_audio_commands_and_service_channels();
        effect->phase++;
        effect->timer = 0;
        break;

    case 13:
        if (read_sound_mode_blocking_status(4) != 1) {
            break;
        }
        effect->phase++;
        effect->timer = 0;
        break;

    case 5:
    case 14:
        if (effect->timer < 7) {
            break;
        }

        effect->phase++;
        effect->timer = 0;
        break;

    case 15:
        if (effect->timer >= 28) {
            play_sound_if_enabled(116);
            effect->phase = 10;
            effect->timer = 0;
        }
        break;
    }

    effect->child_updates = 0;
}
