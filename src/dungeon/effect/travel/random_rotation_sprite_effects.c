#include "shared/audio_commands.h"
/* Launched tile effects, randomized rotating particles, and actor creation at the destination. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/effect/travel/random_rotation_sprite_effects.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/system.h"
#include "dungeon/effect/travel.h"
#include "dungeon/item.h"
#include "dungeon/level.h"

void (*const dungeon_ovl_18b8824_entry)(ovl_18b8824_81898EBC_EffectState *state, ovl_18b8824_81898EBC_Motion *motion, ovl_18b8824_81898EBC_ColorPart *part) = advance_launched_effect;

/* Advances and spins a particle, increments its owner's counter, and removes it after its lifetime. */
void interpolate_view_parameters(void *state, void *motion, void *transform)
{
    u16 tick_count;
    void *linked_state;

    linked_state = *(void **)((s8 *)state + 0xC);
    *(u16 *)((s8 *)linked_state + 0x14) =
        (u16)(*(u16 *)((s8 *)linked_state + 0x14) + 1);
    *(s32 *)((s8 *)motion + 0x00) =
        *(s32 *)((s8 *)motion + 0x00) + *(s32 *)((s8 *)motion + 0x0C);
    *(s32 *)((s8 *)motion + 0x04) =
        *(s32 *)((s8 *)motion + 0x04) + *(s32 *)((s8 *)motion + 0x10);
    *(s32 *)((s8 *)motion + 0x08) =
        *(s32 *)((s8 *)motion + 0x08) + *(s32 *)((s8 *)motion + 0x14);
    *(u16 *)((s8 *)transform + 0x1A) =
        (u16)(*(u16 *)((s8 *)transform + 0x1A) + 0x300);
    tick_count = *(u16 *)((s8 *)state + 0x10) + 1;
    *(u16 *)((s8 *)state + 0x10) = tick_count;
    if (*(s16 *)((s8 *)state + 0x12) < (s16)tick_count) {
        *(u16 *)((s8 *)state - 2) =
            (u16)(*(u16 *)((s8 *)state - 2) | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a randomly rotated half-scale gray sprite with copied motion, an owner link, and a saved
   setting. */
void *create_a_sprite_random_rotation_copies_initial_data(void *context, ovl_18b8824_818988CC_Copy24 *copy_src, s16 initial_value)
{
    ObjectNodeHeader *obj;
    ovl_18b8824_818988CC_S_800240CC_0 *fields;
    SpriteFrameState *sprite;
    ovl_18b8824_818988CC_Copy24 *dst;
    s32 random_value;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = (void *)interpolate_view_parameters;
        fields = (u8 *)obj + 0x20;
        fields->unk_0C = context;
        fields->unk_10 = 0;
        fields->unk_12 = initial_value;

        sprite = obj->sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->source = D_80024E88;
        random_value = rand();
        sprite->angle_z = random_value % 0x1000;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        register_node(obj, project_sprite_chain);
        dst = *(ovl_18b8824_818988CC_Copy24 * *)&obj->position;
        *dst = *copy_src;
        return obj;
    }
    return 0;
}

/*
 * Increments the linked object and entry counters, advances sprite animation, and flags removal
 * when animation flags 0x6000 are set.
 */
void handle_increment_entry_counters_process_target_propagate_status_flags(void *entry, void *unused, SpriteFrameState *target)
{
    void *object;

    object = *(void **)entry;
    *(u16 *)((u8 *)object + 0x14) += 1;
    *(u16 *)((u8 *)entry + 4) += 1;
    advance_sprite_animation_and_textures(target);
    if (target ->flags & 0x6000) {
        *(u16 *)((u8 *)entry - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a gray sprite with copied motion, a fixed rotation, and a starting height offset of 80 units. */
void *create_randomized_grayscale_effect(s32 object_tag, Rec_func_80024264_arg1 *initial_state)
{
    ObjectPosition *state;
    SpriteFrameState *appearance;
    ovl_18b8824_81898A64_S_80024264_0 *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = (void *)handle_increment_entry_counters_process_target_propagate_status_flags;
        appearance = object->unk_0C;
        object->unk_20 = object_tag;
        object->unk_24 = 0;
        appearance->color.c.b = 0x80;
        appearance->color.c.g = 0x80;
        appearance->color.c.r = 0x80;
        select_record_entry_and_value(appearance, &D_80024EF4, 0);
        appearance->scale_x = 0x2000;
        appearance->scale_y = 0x1000;
        appearance->angle_z = 0xC00;
        register_node(object, project_sprite_chain);
        state = object->unk_08;
        state->x.v = initial_state->unk_00.at00_s32.v;
        state->y.v = initial_state->unk_04.at00_s32.v;
        state->z.v = initial_state->unk_08.at00_s32.v + 0x500000;
        state->velocity_x = initial_state->unk_0C.at00_s32.v;
        state->velocity_y = initial_state->unk_10.at00_s32.v;
        state->velocity_z = initial_state->unk_14;
        return object;
    } else {
        return NULL;
    }
}

/* Advances sprite animation, creates a gray child at count 8, and removes the effect at count 16. */
void advance_the_entry_counters_trigger_count_milestones_update_target(void *entry_arg, s32 unused, void *target)
{
    ovl_18b8824_81898B70_S_80024370_0 *entry = entry_arg;
    ovl_18b8824_81898B70_S_80024370_1 *object;
    u16 count;

    object = entry->unk_00;
    object->unk_14++;

    count = entry->unk_04 + 1;
    entry->unk_04 = count;

    switch ((s16)count) {
    case 8:
        create_randomized_grayscale_effect((s32)entry->unk_00, (Rec_func_80024264_arg1 *)unused);
        break;
    case 0x10:
    {
        s32 *global_page;

        global_page = (s32 *)0x80080000;
        ((ovl_18b8824_81898B70_S_80024370_0_pre *)entry)[-1].unk_00 |= 0x8000;
        ((ovl_18b8824_81898B70_S_80024370_2 *)global_page)->unk_14A0 |= 0x8000;
        break;
    }
    }
    advance_sprite_animation_and_textures(target);
}

/* Creates a blue-tinted sprite with copied motion and installs the callback that advances its timed
   target effect. */
void *create_counted_sprite_effect(s32 object_id, ovl_18b8824_81898C1C_S_8002441C_3 *initial_state) {
    SpriteFrameState *display;
    ovl_18b8824_81898C1C_S_8002441C_0 *object;
    ObjectPosition *state;
    void *result;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->unk_10 = (void *)advance_the_entry_counters_trigger_count_milestones_update_target;
        display = object->unk_0C;
        object->unk_20 = object_id;
        object->unk_24 = 0;
        display->color.c.b = 0x80;
        display->color.c.g = 0x80;
        display->color.c.r = 0x80;
        display->color.c.b = 0xC0;
        select_record_entry_and_value(display, &D_80024E40, 0);
        display->scale_x = 0x2000;
        display->scale_y = 0x1000;
        display->clut = 0x7DCF;
        display->flags = (u16)(display->flags | 0xC);
        display->tpage_abr = (u16)(display->tpage_abr | 0x20);
        display->flags = (u16)(display->flags | 0x100);
        register_node(object, project_sprite_chain);
        state = object->unk_08;
        state->x.v = initial_state->unk_00;
        state->y.v = initial_state->unk_04;
        state->z.v = initial_state->unk_08;
        state->velocity_x = initial_state->unk_0C;
        state->velocity_y = initial_state->unk_10;
        state->velocity_z = initial_state->unk_14;
        result = object;
        return result;
    } else {
        result = 0;
        return result;
    }
}

/*
 * Increments the linked object counter and advances sprite animation, setting local and global
 * removal flags when animation flags 0x6000 are set.
 */
void mark_owner_on_target_completion(void *object_ref, s32 unused, SpriteFrameState *target) {
    u8 *object;

    object = *(u8 **)((u8 *)object_ref + 0x0);
    *(u16 *)(object + 0x14) += 1;
    advance_sprite_animation_and_textures(target);
    if (target ->flags & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a gray sprite with copied motion and a 160-unit height offset, signaling its owner when the
   target finishes. */
ovl_18b8824_81898DCC_Object *create_sprite_effect_with_data(s32 field_value, s32 *initial_data) {
    ovl_18b8824_81898DCC_Object *obj;
    u8 *sprite;
    s32 *data;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->callback = (void *)mark_owner_on_target_completion;
        sprite = obj->sprite;
        obj->field20 = field_value;
        sprite[0xE] = 0x80;
        sprite[0xD] = 0x80;
        sprite[0xC] = 0x80;
        ((SpriteFrameState *)sprite)->scale_y = 0x1400;
        ((SpriteFrameState *)sprite)->scale_x = 0x1400;
        select_record_entry_and_value(sprite, D_80024FC4, 0);
        register_node(obj, project_sprite_chain);

        data = obj->data;
        data[0] = initial_data[0];
        data[1] = initial_data[1];
        data[2] = initial_data[2] + 0xA00000;
        data[3] = initial_data[3];
        data[4] = initial_data[4];
        data[5] = initial_data[5];
        return obj;
    }

    return 0;
}

/* Launches an effect toward a checked tile, emits timed visuals, and creates an actor there when allowed. */
void advance_launched_effect(ovl_18b8824_81898EBC_EffectState *state, ovl_18b8824_81898EBC_Motion *motion, ovl_18b8824_81898EBC_ColorPart *part)
{
    void *owner;
    void *owner_data;
    void *owner_node;
    void *source_pos;
    register u8 *origin;
    ovl_18b8824_81898EBC_Scratch scratch;
    u8 *global_page;
    s32 state_id;
    u32 source_z;
    s32 axis;
    u8 *delta_ptr;
    s16 *target_pos;
    s32 target_z;

    state->timer++;
    state_id = state->state;
    owner = state->owner;

    switch (state_id) {
    case 0:

        origin = ((u8 *)&reference_tile_object);
        {
            void *node = ovl_18b8824_81898EBC_PTR_AT((u8 *)owner - 0x20, 0xC);
            s32 dir = (ovl_18b8824_81898EBC_U16_AT(primary_actor_record, 0x2A) >> 9) & 7;
            ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) = get_rounded_facing_and_rounding_flag(ovl_18b8824_81898EBC_U8_AT(node, 0x24), ovl_18b8824_81898EBC_U8_AT(node, 0x25),
                origin[0x24] + dir_step_x[dir], origin[0x25] + dir_step_y[dir], &ovl_18b8824_81898EBC_result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;

    case 1:
        owner_data = (u8 *)owner - 0x20;
        owner_node = ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC);
        if (resolve_record_orientation_or_fallback(ovl_18b8824_81898EBC_PTR_AT(owner_node, 8), owner_node, ovl_18b8824_81898EBC_probe, 0) == 0) {
            if (!(ovl_18b8824_81898EBC_U16_AT(ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
                break;
            }
        }

        source_pos = ovl_18b8824_81898EBC_PTR_AT(owner_data, 8);
        ovl_18b8824_81898EBC_U16_AT(motion, 2) = ovl_18b8824_81898EBC_U16_AT(source_pos, 2);
        ovl_18b8824_81898EBC_U16_AT(motion, 6) = ovl_18b8824_81898EBC_U16_AT(source_pos, 6);
        source_z = ovl_18b8824_81898EBC_U16_AT(source_pos, 0xA);
        ovl_18b8824_81898EBC_U16_AT(motion, 0xA) = source_z;
        if (!(ovl_18b8824_81898EBC_U16_AT(ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
            ovl_18b8824_81898EBC_U16_AT(motion, 2) += ovl_18b8824_81898EBC_probe[0];
            ovl_18b8824_81898EBC_U16_AT(motion, 6) += ovl_18b8824_81898EBC_probe[1];
            ovl_18b8824_81898EBC_U16_AT(motion, 0xA) += ovl_18b8824_81898EBC_probe[2];
        } else {
            ovl_18b8824_81898EBC_U16_AT(motion, 0xA) = source_z - 0x40;
        }
        if (!(ovl_18b8824_81898EBC_U16_AT(state->image, 0) & 0x80)) {
            break;
        }

        target_pos = scratch.work;
        if ((ovl_18b8824_81898EBC_U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            void *direction_node = primary_actor_record;

            state->x = reference_tile_object.tile_position.parts.tile_x + dir_step_x[(ovl_18b8824_81898EBC_U16_AT(direction_node, 0x2A) >> 9) & 7];
            state->y = reference_tile_object.tile_position.parts.tile_y + dir_step_y[(ovl_18b8824_81898EBC_U16_AT(direction_node, 0x2A) >> 9) & 7];
        } else {
            state->x = reference_tile_object.tile_position.parts.tile_x + dir_step_x[state->direction];
            state->y = reference_tile_object.tile_position.parts.tile_y + dir_step_y[state->direction];
        }

        {
            {
                void *height_node;
                s32 tile_coord;

                tile_coord = state->x;
                global_page = (u8 *)0x80080000;
                ovl_18b8824_81898EBC_S16_AT(target_pos, 2) = tile_coord * 64 + 0x20;
                tile_coord = state->y;
                height_node = ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8);
                ovl_18b8824_81898EBC_S16_AT(target_pos, 6) = tile_coord * 64 + 0x20;
                ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) = ((s16 *)height_node)[0x44] - 0x20;
            }
            ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) = get_surface_height_at_record(target_pos);
            state->z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA);
            get_offset_map_cell_value_and_flags(state->x - 1, state->y, 0, &ovl_18b8824_81898EBC_map_flags);
            if (ovl_18b8824_81898EBC_map_flags & 0x3300) {
                s32 fallback_value;

                fallback_value =
                    ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                state->state = 6;
            } else {
                target_z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA);

                if (target_z >= 0x201) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((check_left_tile_and_center_height(ovl_18b8824_81898EBC_U16_AT(target_pos, 2), ovl_18b8824_81898EBC_U16_AT(target_pos, 6), target_z) << 16) != 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((increment_bounded_counter() << 16) == 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else {
                    if ((ovl_18b8824_81898EBC_U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
                        state->status = 1;
                    } else {
                        state->status = 2;
                    }
                    state->state++;
                }
            }

            {
                s32 delta_x;
                s32 raised_z;
                s32 delta_y;
                s32 delta_z;

                axis = 1;
                delta_ptr = (u8 *)&scratch + 2;
                delta_x = ovl_18b8824_81898EBC_S16_AT(target_pos, 2) - ovl_18b8824_81898EBC_S16_AT(motion, 2);
                delta_x = abs(delta_x);
                ovl_18b8824_81898EBC_probe[0] = delta_x;
                delta_y = ovl_18b8824_81898EBC_S16_AT(target_pos, 6) - ovl_18b8824_81898EBC_S16_AT(motion, 6);
                delta_y = abs(delta_y);
                ovl_18b8824_81898EBC_probe[1] = delta_y;
                raised_z = ovl_18b8824_81898EBC_S16_AT(motion, 0xA) + 160;
                delta_z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) - raised_z;
                delta_z = abs(delta_z);
                ovl_18b8824_81898EBC_probe[2] = delta_z;
                state->duration = delta_x;
            }
            do {
                s32 axis_delta;

                axis_delta = ovl_18b8824_81898EBC_S16_AT(delta_ptr, 24);
                if (state->duration < axis_delta) {
                    state->duration = ovl_18b8824_81898EBC_U16_AT(delta_ptr, 24);
                }
                axis++;
                delta_ptr += 2;
            } while (axis < 3);
            state->duration =
                (state->duration >> 4) + (state->duration >> 5);
            if (state->duration == 0) {
                state->duration = 1;
            }
            ovl_18b8824_81898EBC_S32_AT(motion, 0xC) =
                (ovl_18b8824_81898EBC_S32_AT(target_pos, 0) - ovl_18b8824_81898EBC_S32_AT(motion, 0)) / state->duration;
            {
                s32 current_y;
                s32 y_step;
                s32 move_frames;

                current_y = ovl_18b8824_81898EBC_S32_AT(motion, 4);
                y_step = ovl_18b8824_81898EBC_S32_AT(target_pos, 4) - current_y;
                move_frames = state->duration;
                y_step /= move_frames;
                ovl_18b8824_81898EBC_S32_AT(motion, 0x10) = y_step;
            }
            {
                s32 raised_z;
                s32 z_offset;

                z_offset = 0x00A00000;
                raised_z = ovl_18b8824_81898EBC_S32_AT(motion, 8) + z_offset;
                ovl_18b8824_81898EBC_S32_AT(motion, 0x14) =
                    (ovl_18b8824_81898EBC_S32_AT(target_pos, 8) - raised_z) / state->duration;
            }
            create_a_sprite_random_rotation_copies_initial_data(state, motion, state->duration);
            create_a_sprite_random_rotation_copies_initial_data(state, motion, state->duration);
            create_a_sprite_random_rotation_copies_initial_data(state, motion, state->duration);
            state->timer = 0;
            break;
        }

    case 2:
        ovl_18b8824_81898EBC_S32_AT(motion, 0) += ovl_18b8824_81898EBC_S32_AT(motion, 0xC);
        ovl_18b8824_81898EBC_S32_AT(motion, 4) += ovl_18b8824_81898EBC_S32_AT(motion, 0x10);
        ovl_18b8824_81898EBC_S32_AT(motion, 8) += ovl_18b8824_81898EBC_S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            break;
        }
        create_counted_sprite_effect(state, motion);
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        state->timer = 0;
        state->state++;
        break;

    case 3:
        if (state->timer < 0x10) {
            break;
        }
        create_sprite_effect_with_data(state, motion);
        state->timer = 0;
        state->state++;
        break;

    case 4:
        if (state->timer < 0x11) {
            break;
        }
        if (state->status != 0) {
            void *effect = create_actor_sprite_at_tile(state->status, state->x, state->y,
                                         state->z);
            s32 intensity;
            s16 clamped_intensity;
            u32 effect_id;
            s32 random_bits;

            func_80042640(effect, 52);
            random_bits = generate_random_value();
            effect_id = ovl_18b8824_81898EBC_U8_AT(state, 9);
            intensity = effect_id >> 1;
            intensity += effect_id << 1;
            intensity += random_bits & 3;
            intensity += 16;
            clamped_intensity = intensity;
            if (intensity >= 256) {
                clamped_intensity = 255;
            }
            ovl_18b8824_81898EBC_U8_AT(effect, 0x28) = clamped_intensity;
            ovl_18b8824_81898EBC_U8_AT(effect, 0x29) = clamped_intensity;
        }
        state->timer = 0;
        state->state++;
        break;

    case 5:
        if (state->field_14 != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        ovl_18b8824_81898EBC_U16_AT(state, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 6:
        ovl_18b8824_81898EBC_S32_AT(motion, 0) += ovl_18b8824_81898EBC_S32_AT(motion, 0xC);
        ovl_18b8824_81898EBC_S32_AT(motion, 4) += ovl_18b8824_81898EBC_S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

    state->field_14 = 0;
}
