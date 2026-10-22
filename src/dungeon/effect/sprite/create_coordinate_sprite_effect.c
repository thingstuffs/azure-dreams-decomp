/* Positioned sprite creation, radial height cycling, randomized rotation, and actor value changes. */
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

/* Adds a random actor value delta with an optional half bonus, clamps it, displays a popup, and
   applies it. */
void func_80024028(void *target, s32 effect_param) {
    s32 base_gain;
    register s32 stat_gain;

    if (try_trigger_target_record_effect(target, 1) == 0) {
        base_gain = get_random_scaled_value(effect_param & 0xFF) + 4;
        stat_gain = base_gain;
        if (*(u8 *)((u8 *)target + 0x28) & 1) {
            stat_gain = base_gain + ((s32)(base_gain << 16) >> 17);
        }
        *(u16 *)((u8 *)target + 0x64) += stat_gain;
        cap_pending_actor_value_delta(target);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        apply_clamped_actor_value_delta(target);
    }
}

void animate_randomly_rotated_sprite(Row_818A48C4_Func818A48C4Object **source_ref, s32 unused,
                   SpriteFrameState *target) {
    Row_818A48C4_Func818A48C4Object *source;
    s32 random_value;

    source = *source_ref;
    source->flags += 1;
    advance_sprite_animation_and_textures(target);
    random_value = rand();
    target->angle_z = (s16)(random_value % 0x1000);
    if (target->flags & 0x6000) {
        select_record_entry_and_value(target, D_80025238, 0);
    }
}

/* Creates a gray half-scale animated sprite at the supplied coordinates and stores the user data. */
void *create_coordinate_sprite_effect(s32 user_data, Row_818A4948_S_func_818A4948_2 *source_coords) {
    Row_818A4948_S_func_818A4948_0 *obj;
    SpriteFrameState *render_data;
    ObjectPosition *coords;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->unk_10 = animate_randomly_rotated_sprite;
        render_data = obj->unk_0C;
        obj->unk_20 = user_data;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        select_record_entry_and_value(render_data, D_80025238, 0);
        render_data->scale_y = 0x800;
        render_data->scale_x = 0x800;
        render_data->clut = 0x7E07;
        render_data->flags |= 0x100;
        register_node(obj, (s32) project_sprite_chain);
        coords = obj->unk_08;
        coords->x.w.i = source_coords->unk_02;
        coords->y.w.i = source_coords->unk_06;
        coords->z.w.i = source_coords->unk_0A;
        return obj;
    }
    return 0;
}

void advance_counted_sprite_animation(void **object_ref, long long value) {
    void *object;
    u16 *counter;
    u32 low_value;

    object = *object_ref;
    counter = (u16 *)((s8 *)object + 0x14);
    low_value = value;
    *counter = (u16)(*counter + 1);
    advance_sprite_animation_and_textures(low_value);
}

/* Creates an initially black, full-scale animated sprite at the supplied coordinates and links it to
   its context. */
void *create_randomized_grayscale_effect(s32 context_value, Row_818A4A64_S_818A4A64_2 *initial_position) {
    SpriteFrameState *render_state;
    Row_818A4A64_S_818A4A64_0 *object;
    ObjectPosition *position;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        render_state = object->unk_0C;
        object->unk_10 = (s32 *) advance_counted_sprite_animation;
        object->unk_20 = context_value;
        render_state->color.c.b = 0;
        render_state->color.c.g = 0;
        render_state->color.c.r = 0;
        select_record_entry_and_value(render_state, D_800DEAE0, 0);
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->flags |= 0xC;
        register_node(object, (s32) project_sprite_chain);
        position = object->unk_08;
        position->x.w.i = initial_position->unk_02;
        position->y.w.i = initial_position->unk_06;
        position->z.w.i = initial_position->unk_0A;
        return object;
    }
    return NULL;
}

/* Steps a sprite's height, resets its radial position at the height limit, and restarts its completed
   animation. */
void cycle_sprite_height_and_position(Row_818A4B40_S_818A4B40_0 *motion, Row_818A4B40_S_818A4B40_2 *position, SpriteFrameState *object) {
    s16 angle;
    s32 random_value;
    s32 biased_random;
    u16 height_offset;
    Row_818A4B40_S_818A4B40_1 *counter;

    counter = motion->unk_00;
    counter->unk_14 = (u16) (counter->unk_14 + 1);
    height_offset = motion->unk_04 + motion->unk_06;
    motion->unk_04 = height_offset;
    if ((s16) height_offset < -0x80) {
        random_value = rand();
        biased_random = random_value;
        angle = (random_value % 4096);
        position->unk_02 = (s16) (motion->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (motion->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        motion->unk_04 = (u16) (motion->unk_04 + 0x80);
        motion->unk_06 = (u16) (-6 - (rand() % 5));
    }
    position->unk_0A = (s16) (motion->unk_0C + motion->unk_04);
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, &D_800DECF8, 0);
    }
}

/* Creates a gray animated sprite around the origin at a random angle, with a randomized vertical step. */
s32 create_random_radial_effect(Row_818A4CA0_S_818A4CA0_1 *effect_data, Row_818A4CA0_S_818A4CA0_2 *origin, s16 effect_param, s16 frame_index) {
    s32 result;
    s16 angle;
    u16 height;
    s32 shifted_frame;
    s32 random_value;
    s32 biased_random;

    SpriteFrameState *sprite;
    ObjectPosition *position;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        random_value = (s32)cycle_sprite_height_and_position;
        ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_20 = effect_data;
        effect_data = ((void *)effect) + 0x20;
        effect->unk_10 = (void *)random_value;
        effect_data->unk_04 = effect_param;
        effect_data->unk_06 = (s16) (-6 - (rand() % 5));
        effect_data->unk_08 = (u16) origin->unk_02;
        effect_data->unk_0A = (u16) origin->unk_06;
        effect_data->unk_0C = (u16) (origin->unk_0A + 0x20);
        sprite = effect->sprite;
        sprite->color.c.b = 0x60;
        sprite->color.c.g = 0x60;
        sprite->color.c.r = 0x60;
        sprite->clut = 0x7E07;
        sprite->tpage_abr = (u16) (sprite->tpage_abr | 0x60);
        sprite->flags = (u16) (sprite->flags | 0x100);
        shifted_frame = (s32)frame_index << 0x10;
        select_record_entry_and_value(sprite, &D_800DECF8, (s16) ((shifted_frame >> 0x10) % 5));
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        register_node(effect, project_sprite_chain);
        position = effect->position;
        random_value = rand();
        biased_random = random_value;
        angle = (random_value % 4096);
        position->x.w.i = (s16) (effect_data->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->y.w.i = (s16) (effect_data->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        height = effect_data->unk_0C;
        result = (s32)effect;
        position->z.w.i = (s16)height;
        return result;
    }
    result = 0;
    return result;
}

void randomize_counted_sprite_angle(void **object_ref, s32 unused, Row_818A4E74_S_func_818A4E74_1 *target) {
    s32 random_value;
    s32 random_quotient;
    Row_818A4E74_S_func_818A4E74_0 *object;

    object = *object_ref;
    object->unk_14 = (u16)(object->unk_14 + 1);
    random_value = rand();
    random_quotient = random_value / 0x1000;
    target->unk_1A = (s16)(random_value - (random_quotient << 12));
}

/* Creates an initially black, zero-scale sprite at the supplied coordinates with a random rotation. */
s32 create_randomly_rotated_effect(s32 object_param, Row_818A4ED0_S_818A4ED0_3 *spawn_position) {
    s32 rotation_rng;
    SpriteFrameState *render_state;
    ObjectPosition *position;
    Row_818A4ED0_S_818A4ED0_0 *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = randomize_counted_sprite_angle;
        object->unk_20 = object_param;
        render_state = object->unk_0C;
        render_state->source = D_80025214;
        render_state->clut = 0x7E07;
        render_state->color.c.b = 0;
        render_state->color.c.g = 0;
        render_state->color.c.r = 0;
        render_state->tpage_abr = (u16) (render_state->tpage_abr | 0x60);
        render_state->flags = (u16) (render_state->flags | 0x10C);
        rotation_rng = rand();
        render_state->angle_z = (s16) (rotation_rng % 0x1000);
        render_state->scale_y = 0;
        render_state->scale_x = 0;
        register_node(object, project_sprite_chain);
        position = object->unk_08;
        {
            s32 unused_rng;
            unused_rng = rand();
        }
        position->x.w.i = (u16) spawn_position->unk_02;
        position->y.w.i = (u16) spawn_position->unk_06;
        {
            u16 final_z = spawn_position->unk_0A;
            position->z.w.i = final_z;
            return (s32)object;
        }
    }
    {
        s32 failure_result;
        failure_result = 0;
        return failure_result;
    }
}
