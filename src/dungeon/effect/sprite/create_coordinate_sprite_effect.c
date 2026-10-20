#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

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

#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void func_800240C4(Row_818A48C4_Func818A48C4Object **source_ref, s32 unused,
                   Row_818A48C4_Func818A48C4Object *target) {
    Row_818A48C4_Func818A48C4Object *source;
    s32 random_value;

    source = *source_ref;
    source->flags += 1;
    func_800478B8(target);
    random_value = rand();
    target->value = (s16)(random_value % 0x1000);
    if (target->flags & 0x6000) {
        func_8003DB94(target, D_80025238, 0);
    }
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void *create_coordinate_sprite_effect(s32 user_data, Row_818A4948_S_func_818A4948_2 *source_coords) {
    Row_818A4948_S_func_818A4948_0 *obj;
    Row_818A4948_S_func_818A4948_1 *render_data;
    Row_818A4948_S_func_818A4948_2 *coords;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk_10 = func_800240C4;
        render_data = obj->unk_0C;
        obj->unk_20 = user_data;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        func_8003DB94(render_data, D_80025238, 0);
        render_data->unk_1E = 0x800;
        render_data->unk_1C = 0x800;
        render_data->unk_12 = 0x7E07;
        render_data->unk_14 |= 0x100;
        register_node(obj, (s32) project_sprite_chain);
        coords = obj->unk_08;
        coords->unk_02 = source_coords->unk_02;
        coords->unk_06 = source_coords->unk_06;
        coords->unk_0A = source_coords->unk_0A;
        return obj;
    }
    return 0;
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void func_80024230(void **object_ref, long long value) {
    void *object;
    u16 *counter;
    u32 low_value;

    object = *object_ref;
    counter = (u16 *)((s8 *)object + 0x14);
    low_value = value;
    *counter = (u16)(*counter + 1);
    func_800478B8(low_value);
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void *create_randomized_grayscale_effect(s32 context_value, Row_818A4A64_S_818A4A64_2 *initial_position) {
    Row_818A4A64_S_818A4A64_1 *render_state;
    Row_818A4A64_S_818A4A64_0 *object;
    Row_818A4A64_S_818A4A64_3 *position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        render_state = object->unk_0C;
        object->unk_10 = (s32 *) func_80024230;
        object->unk_20 = context_value;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        func_8003DB94(render_state, D_800DEAE0, 0);
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_14 |= 0xC;
        register_node(object, (s32) project_sprite_chain);
        position = object->unk_08;
        position->unk_02 = initial_position->unk_02;
        position->unk_06 = initial_position->unk_06;
        position->unk_0A = initial_position->unk_0A;
        return object;
    }
    return NULL;
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void func_80024340(Row_818A4B40_S_818A4B40_0 *motion, Row_818A4B40_S_818A4B40_2 *position, Rec_D_80082E80 *object) {
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
    func_800478B8(object);
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(object, &D_800DECF8, 0);
    }
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

s32 create_random_radial_effect(Row_818A4CA0_S_818A4CA0_1 *effect_data, Row_818A4CA0_S_818A4CA0_2 *origin, s16 effect_param, s16 frame_index) {
    s32 result;
    s16 angle;
    u16 height;
    s32 shifted_frame;
    s32 random_value;
    s32 biased_random;

    Row_818A4CA0_S_818A4CA0_3 *sprite;
    Row_818A4CA0_S_818A4CA0_4 *position;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        random_value = (s32)func_80024340;
        ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_20 = effect_data;
        effect_data = effect + 0x20;
        ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_10 = (void *)random_value;
        effect_data->unk_04 = effect_param;
        effect_data->unk_06 = (s16) (-6 - (rand() % 5));
        effect_data->unk_08 = (u16) origin->unk_02;
        effect_data->unk_0A = (u16) origin->unk_06;
        effect_data->unk_0C = (u16) (origin->unk_0A + 0x20);
        sprite = ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_0C;
        sprite->unk_0E = 0x60;
        sprite->unk_0D = 0x60;
        sprite->unk_0C = 0x60;
        sprite->unk_12 = 0x7E07;
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x60);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        shifted_frame = (s32)frame_index << 0x10;
        func_8003DB94(sprite, &D_800DECF8, (s16) ((shifted_frame >> 0x10) % 5));
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        register_node(effect, project_sprite_chain);
        position = ((Row_818A4CA0_S_818A4CA0_0 *)effect)->unk_08;
        random_value = rand();
        biased_random = random_value;
        angle = (random_value % 4096);
        position->unk_02 = (s16) (effect_data->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (effect_data->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        height = effect_data->unk_0C;
        result = (s32)effect;
        position->unk_0A = (s16)height;
        return result;
    }
    result = 0;
    return result;
}

#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

void func_80024674(void **object_ref, s32 unused, Row_818A4E74_S_func_818A4E74_1 *target) {
    s32 random_value;
    s32 random_quotient;
    Row_818A4E74_S_func_818A4E74_0 *object;

    object = *object_ref;
    object->unk_14 = (u16)(object->unk_14 + 1);
    random_value = rand();
    random_quotient = random_value / 0x1000;
    target->unk_1A = (s16)(random_value - (random_quotient << 12));
}
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"

s32 create_randomly_rotated_effect(s32 object_param, Row_818A4ED0_S_818A4ED0_3 *spawn_position) {
    s32 rotation_rng;
    Row_818A4ED0_S_818A4ED0_1 *render_state;
    Row_818A4ED0_S_818A4ED0_2 *position;
    Row_818A4ED0_S_818A4ED0_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = func_80024674;
        object->unk_20 = object_param;
        render_state = object->unk_0C;
        render_state->unk_08 = D_80025214;
        render_state->unk_12 = 0x7E07;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x10C);
        rotation_rng = rand();
        render_state->unk_1A = (s16) (rotation_rng % 0x1000);
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        register_node(object, project_sprite_chain);
        position = object->unk_08;
        {
            s32 unused_rng;
            unused_rng = rand();
        }
        position->unk_02 = (u16) spawn_position->unk_02;
        position->unk_06 = (u16) spawn_position->unk_06;
        {
            u16 final_z = spawn_position->unk_0A;
            position->unk_0A = final_z;
            return (s32)object;
        }
    }
    {
        s32 failure_result;
        failure_result = 0;
        return failure_result;
    }
}
