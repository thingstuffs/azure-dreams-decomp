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

void (*const dungeon_ovl_18b8824_entry)(LaunchedEffectBody *state, ObjectPosition *motion, ovl_18b8824_81898EBC_ColorPart *part) = advance_launched_effect;

/* Advances and spins a particle, increments its owner's counter, and removes it after its lifetime. */
void interpolate_view_parameters(RandomRotationSpriteEffectBody *state, ObjectPosition *motion, SpriteFrameState *transform)
{
    s16 tick_count;
    LaunchedEffectBody *linked_state;

    linked_state = state->owner;
    linked_state->child_updates++;
    motion->x.v =
        motion->x.v + motion->velocity_x;
    motion->y.v =
        motion->y.v + motion->velocity_y;
    motion->z.v =
        motion->z.v + motion->velocity_z;
    transform->angle_z += 0x300;
    tick_count = state->ticks + 1;
    state->ticks = tick_count;
    if (state->lifetime < tick_count) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a randomly rotated half-scale gray sprite with copied motion, an owner link, and a saved
   setting. */
void *create_random_rotation_sprite_effect(LaunchedEffectBody *context, ObjectPosition *copy_src, s16 initial_value)
{
    ObjectNodeHeader *obj;
    RandomRotationSpriteEffectBody *fields;
    SpriteFrameState *sprite;
    ObjectPosition *dst;
    s32 random_value;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = interpolate_view_parameters;
        fields = NODE_BODY(obj);
        fields->owner = context;
        fields->ticks = 0;
        fields->lifetime = initial_value;

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
        dst = obj->position;
        *dst = *copy_src;
        return obj;
    }
    return 0;
}

/*
 * Increments the linked object and entry counters, advances sprite animation, and flags removal
 * when animation flags 0x6000 are set.
 */
void update_randomized_grayscale_effect(RandomizedGrayscaleEffectBody *entry, ObjectPosition *unused, SpriteFrameState *target)
{
    LaunchedEffectBody *object;

    object = entry->owner;
    object->child_updates += 1;
    entry->ticks += 1;
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        NODE_HEADER(entry)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a gray sprite with copied motion, a fixed rotation, and a starting height offset of 80 units. */
void *create_randomized_grayscale_effect(LaunchedEffectBody *owner, ObjectPosition *initial_state)
{
    ObjectPosition *state;
    SpriteFrameState *appearance;
    ObjectNodeHeader *object;
    RandomizedGrayscaleEffectBody *body;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->update_callback = update_randomized_grayscale_effect;
        appearance = object->sprite;
        body = NODE_BODY(object);
        body->owner = owner;
        body->ticks = 0;
        appearance->color.c.b = 0x80;
        appearance->color.c.g = 0x80;
        appearance->color.c.r = 0x80;
        select_record_entry_and_value(appearance, &D_80024EF4, 0);
        appearance->scale_x = 0x2000;
        appearance->scale_y = 0x1000;
        appearance->angle_z = 0xC00;
        register_node(object, project_sprite_chain);
        state = object->position;
        state->x.v = initial_state->x.v;
        state->y.v = initial_state->y.v;
        state->z.v = initial_state->z.v + 0x500000;
        state->velocity_x = initial_state->velocity_x;
        state->velocity_y = initial_state->velocity_y;
        state->velocity_z = initial_state->velocity_z;
        return object;
    } else {
        return NULL;
    }
}

/* Advances sprite animation, creates a gray child at count 8, and removes the effect at count 16. */
void update_counted_sprite_effect(CountedSpriteEffectBody *entry, ObjectPosition *position, SpriteFrameState *target)
{
    LaunchedEffectBody *object;
    s16 count;

    object = entry->owner;
    object->child_updates++;

    count = entry->ticks + 1;
    entry->ticks = count;

    switch (count) {
    case 8:
        create_randomized_grayscale_effect(entry->owner, position);
        break;
    case 0x10:
    {
        u8 *global_page;

        global_page = (u8 *)0x80080000;
        NODE_HEADER(entry)->flags |= NODE_REMOVE;
        ((ObjectFlagBlock *)(global_page + 0x14A0))->flags |= OBJECT_REMOVE_PENDING;
        break;
    }
    }
    advance_sprite_animation_and_textures(target);
}

/* Creates a blue-tinted sprite with copied motion and installs the callback that advances its timed
   target effect. */
void *create_counted_sprite_effect(LaunchedEffectBody *owner, ObjectPosition *initial_state) {
    SpriteFrameState *display;
    ObjectNodeHeader *object;
    CountedSpriteEffectBody *body;
    ObjectPosition *state;
    void *result;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->update_callback = update_counted_sprite_effect;
        display = object->sprite;
        body = NODE_BODY(object);
        body->owner = owner;
        body->ticks = 0;
        display->color.c.b = 0x80;
        display->color.c.g = 0x80;
        display->color.c.r = 0x80;
        display->color.c.b = 0xC0;
        select_record_entry_and_value(display, &D_80024E40, 0);
        display->scale_x = 0x2000;
        display->scale_y = 0x1000;
        display->clut = 0x7DCF;
        display->flags |= 0xC;
        display->tpage_abr |= 0x20;
        display->flags |= 0x100;
        register_node(object, project_sprite_chain);
        state = object->position;
        state->x.v = initial_state->x.v;
        state->y.v = initial_state->y.v;
        state->z.v = initial_state->z.v;
        state->velocity_x = initial_state->velocity_x;
        state->velocity_y = initial_state->velocity_y;
        state->velocity_z = initial_state->velocity_z;
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
void animate_sprite_once_counting_owner_ticks(SpriteEffectWithDataBody *object_ref, ObjectPosition *unused, SpriteFrameState *target) {
    LaunchedEffectBody *object;

    object = object_ref->owner;
    object->child_updates += 1;
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        NODE_HEADER(object_ref)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a gray sprite with copied motion and a 160-unit height offset, signaling its owner when the
   target finishes. */
ObjectNodeHeader *create_sprite_effect_with_data(LaunchedEffectBody *owner, ObjectPosition *initial_data) {
    ObjectNodeHeader *obj;
    SpriteEffectWithDataBody *body;
    SpriteFrameState *sprite;
    ObjectPosition *data;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = animate_sprite_once_counting_owner_ticks;
        sprite = obj->sprite;
        body = NODE_BODY(obj);
        body->owner = owner;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1400;
        sprite->scale_x = 0x1400;
        select_record_entry_and_value(sprite, D_80024FC4, 0);
        register_node(obj, project_sprite_chain);

        data = obj->position;
        data->x.v = initial_data->x.v;
        data->y.v = initial_data->y.v;
        data->z.v = initial_data->z.v + 0xA00000;
        data->velocity_x = initial_data->velocity_x;
        data->velocity_y = initial_data->velocity_y;
        data->velocity_z = initial_data->velocity_z;
        return obj;
    }

    return 0;
}

/* Launches an effect toward a checked tile, emits timed visuals, and creates an actor there when allowed. */
void advance_launched_effect(LaunchedEffectBody *state, ObjectPosition *motion, ovl_18b8824_81898EBC_ColorPart *part)
{
    void *owner;
    ObjectNodeHeader *owner_header;
    SpriteFrameState *owner_sprite;
    ObjectPosition *source_pos;
    TileObject *origin;
    ovl_18b8824_81898EBC_Scratch scratch;
    u8 *global_page;
    s32 state_id;
    u16 source_z;
    s32 axis;
    u8 *delta_ptr;
    s16 *target_pos;
    s32 target_z;

    state->timer++;
    state_id = state->state;
    owner = state->owner;

    switch (state_id) {
    case 0:

        origin = &reference_tile_object;
        {
            SpriteFrameState *node = NODE_HEADER(owner)->sprite;
            s32 dir = (primary_actor_record->facing >> 9) & 7;
            ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) = get_rounded_facing_and_rounding_flag(node->tile_x, node->tile_y,
                origin->tile_position.parts.tile_x + dir_step_x[dir], origin->tile_position.parts.tile_y + dir_step_y[dir], &ovl_18b8824_81898EBC_result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;

    case 1:
        owner_header = NODE_HEADER(owner);
        owner_sprite = owner_header->sprite;
        if (resolve_record_orientation_or_fallback(owner_sprite->source, owner_sprite, ovl_18b8824_81898EBC_probe, 0) == 0) {
            if (!(owner_header->sprite->flags & 0x8000)) {
                break;
            }
        }

        source_pos = owner_header->position;
        motion->x.w.i = source_pos->x.w.i;
        motion->y.w.i = source_pos->y.w.i;
        source_z = source_pos->z.w.i;
        motion->z.w.i = source_z;
        if (!(owner_header->sprite->flags & 0x8000)) {
            motion->x.w.i += ovl_18b8824_81898EBC_probe[0];
            motion->y.w.i += ovl_18b8824_81898EBC_probe[1];
            motion->z.w.i += ovl_18b8824_81898EBC_probe[2];
        } else {
            motion->z.w.i = source_z - 0x40;
        }
        if (!(ovl_18b8824_81898EBC_U16_AT(state->image, 0) & 0x80)) {
            break;
        }

        target_pos = scratch.work;
        if ((owner_header->flags | 0x2000) != 0) {
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
                    if ((owner_header->flags | 0x2000) != 0) {
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
                delta_x = ovl_18b8824_81898EBC_S16_AT(target_pos, 2) - motion->x.w.i;
                delta_x = abs(delta_x);
                ovl_18b8824_81898EBC_probe[0] = delta_x;
                delta_y = ovl_18b8824_81898EBC_S16_AT(target_pos, 6) - motion->y.w.i;
                delta_y = abs(delta_y);
                ovl_18b8824_81898EBC_probe[1] = delta_y;
                raised_z = motion->z.w.i + 160;
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
            motion->velocity_x =
                (ovl_18b8824_81898EBC_S32_AT(target_pos, 0) - motion->x.v) / state->duration;
            {
                s32 current_y;
                s32 y_step;
                s32 move_frames;

                current_y = motion->y.v;
                y_step = ovl_18b8824_81898EBC_S32_AT(target_pos, 4) - current_y;
                move_frames = state->duration;
                y_step /= move_frames;
                motion->velocity_y = y_step;
            }
            {
                s32 raised_z;
                s32 z_offset;

                z_offset = 0x00A00000;
                raised_z = motion->z.v + z_offset;
                motion->velocity_z =
                    (ovl_18b8824_81898EBC_S32_AT(target_pos, 8) - raised_z) / state->duration;
            }
            create_random_rotation_sprite_effect(state, motion, state->duration);
            create_random_rotation_sprite_effect(state, motion, state->duration);
            create_random_rotation_sprite_effect(state, motion, state->duration);
            state->timer = 0;
            break;
        }

    case 2:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
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
            effect_id = state->id;
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
        if (state->child_updates != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        NODE_HEADER(state)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 6:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

    state->child_updates = 0;
}
