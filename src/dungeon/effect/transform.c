/* Copied-motion sprite creation with random rotation and timed grayscale growth. */
#include "dungeon/effect/transform.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/transform.h"

/* Creates a gray, randomly rotated sprite with copied motion, a saved starting height, and the
   supplied tag. */
ObjectNodeHeader *allocate_display_object_and_copy_state(void *stored_value, ObjectPosition *input, s16 stored_tag) {
    s32 random_or_w2;
    s32 rounded_random;
    ObjectNodeHeader *object;
    Row_8189E934_Tail *state;
    SpriteFrameState *display;
    ObjectPosition *input_copy;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = (void *)object + 0x20;
        object->update_callback = D_80024020;
        state->value = stored_value;
        state->pad0 = 0;
        state->tag = stored_tag;
        display = object->sprite;
        display->color.c.b = 0x80;
        display->color.c.g = 0x80;
        display->color.c.r = 0x80;
        display->source = D_80024C78;
        display->clut = 0x7E02;
        display->flags |= 0x100;
        rounded_random = rand();
        random_or_w2 = rounded_random;
        display->angle_z = random_or_w2 % 4096;
        display->scale_y = 0x800;
        display->scale_x = 0x800;
        register_node(object, project_sprite_chain);
        input_copy = object->position;
        *input_copy = *input;
        random_or_w2 = input_copy->z.v;
        state->copy = random_or_w2;
        return object;
    }
    return 0;
}

/* Advances sprite animation and three timed stages of grayscale brightening and horizontal or vertical
   growth. */
void create_randomized_grayscale_effect(Row_8189EA64_S_80024264_0 *sequence, s32 unused, SpriteFrameState *record)
{
    s16 word_or_frame;
    s16 state;
    s32 next_high_word;
    Row_8189EA64_S_80024264_1 *owner;

    owner = sequence->unk_08;
    owner->unk_14++;
    sequence->unk_02.u++;
    advance_sprite_animation_and_textures(record);

    state = sequence->unk_00.s;
    switch (state) {
    case 0:
    {
        u8 channel_value;
        u16 low_word;

        channel_value = record->color.c.b;
        word_or_frame = record->scale_y;
        channel_value++;
        record->color.c.b = channel_value;
        record->color.c.g = channel_value;
        record->color.c.r = channel_value;
        low_word = record->scale_x;
        word_or_frame += 0x10;
        record->scale_y = word_or_frame;
        low_word += 0x100;
        record->scale_x = low_word;
        if (sequence->unk_02.s < sequence->unk_04) {
            return;
        }
        sequence->unk_02.u = 0;
        sequence->unk_00.u++;
        return;
    }
    case 1:
    {
        u8 channel_value;
        u16 low_word;

        channel_value = record->color.c.b;
        low_word = record->scale_x;
        channel_value++;
        low_word += 0x80;
        record->color.c.b = channel_value;
        record->color.c.g = channel_value;
        record->color.c.r = channel_value;
        record->scale_x = low_word;
        next_high_word = sequence->unk_02.s << 8;
        record->scale_y = next_high_word;
        if (sequence->unk_02.s < sequence->unk_04) {
            return;
        }
        sequence->unk_02.u = 0;
        sequence->unk_00.u++;
        return;
    }
    case 2:
    {
        u8 channel_value;

        channel_value = record->color.c.b + 6;
        record->color.c.b = channel_value;
        record->color.c.g = channel_value;
        record->color.c.r = channel_value;
        word_or_frame = sequence->unk_02.s;

        next_high_word = (word_or_frame + 0x10) << 8;
        record->scale_y = next_high_word;
        if (sequence->unk_02.s < sequence->unk_04) {
            return;
        }
        sequence->unk_02.u = 0;
        sequence->unk_00.u++;
        return;
    }
    case 3:
        advance_sprite_animation_and_textures(record);
        return;
    default:
        return;
    }
}

/* Creates an initially black, zero-scale sprite with copied motion and a random starting animation frame. */
ObjectNodeHeader *create_randomized_transform_effect(void *owner_id, ObjectPosition *transform)
{
    s32 random_value;
    s32 rounded_random;
    ObjectNodeHeader *return_value;
    SpriteFrameState *sprite;
    ObjectNodeHeader *object;
    Row_8189EBBC_S_800243BC_1 *state;
    ObjectPosition *object_transform;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = ((void *)object) + 0x20;
        object->update_callback = &D_80024264;
        state->unk_08 = owner_id;
        state->phase = 0;
        state->unk_02 = 0;
        state->unk_04 = 0x10;
        sprite = object->sprite;
        sprite->clut = 0x7E02;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        sprite->scale_y = 0;
        sprite->scale_x = 0;
        sprite->flags |= 0xC;
        sprite->tpage_abr |= 0x20;
        sprite->flags |= 0x100;
        random_value = rand();
        rounded_random = random_value;
        if (random_value < 0) {
            rounded_random = random_value + 0xF;
        }
        select_record_entry_and_value(sprite, &D_800DEF08,
                      (s16)(random_value - ((rounded_random >> 4) * 0x10)));
        register_node(object, &transform_effect_tag);
        object_transform = object->position;
        return_value = object;
        *object_transform = *transform;
        return return_value;
    }
    return 0;
}
