#include "dungeon/effect/transform.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/transform.h"

s32 allocate_display_object_and_copy_state(s32 stored_value, void *input, s16 stored_tag) {
    s32 random_or_w2;
    s32 rounded_random;
    void *object;
    Row_8189E934_Tail *state;
    SpriteFrameState *display;
    void *input_copy;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = (Row_8189E934_Tail *)((s8 *)object + 0x20);
        ((Row_8189E934_S_80024134_0 *)object)->unk_10 = D_80024020;
        state->value = stored_value;
        ((Row_8189E934_S_80024134_0 *)object)->unk_20 = 0;
        state->tag = stored_tag;
        display = ((Row_8189E934_S_80024134_0 *)object)->unk_0C;
        display->color.c.b = 0x80;
        display->color.c.g = 0x80;
        display->color.c.r = 0x80;
        display->source = D_80024C78;
        display->clut = 0x7E02;
        display->flags = (u16) (display->flags | 0x100);
        rounded_random = rand();
        random_or_w2 = rounded_random;
        display->angle_z = (s16) (random_or_w2 % 4096);
        display->scale_y = 0x800;
        display->scale_x = 0x800;
        register_node(object, project_sprite_chain);
        input_copy = ((Row_8189E934_S_80024134_0 *)object)->unk_08;
        *(Row_8189E934_Input6 *)input_copy = *(Row_8189E934_Input6 *)input;
        random_or_w2 = *(s32 *)((s8 *)input_copy + 8);
        state->copy = random_or_w2;
        return (s32)object;
    }
    return 0;
}

void create_randomized_grayscale_effect(Row_8189EA64_S_80024264_0 *sequence, s32 unused, Rec_D_80082E80 *record)
{
    s16 word_or_frame;
    s16 state;
    s32 next_high_word;
    Row_8189EA64_S_80024264_1 *owner;

    owner = sequence->unk_08;
    owner->unk_14++;
    sequence->unk_02.u++;
    func_800478B8(record);

    state = sequence->unk_00.s;
    switch (state) {
    case 0:
    {
        u8 channel_value;
        u16 low_word;

        channel_value = ((SpriteFrameState *)record)->color.c.b;
        word_or_frame = ((SpriteFrameState *)record)->scale_y;
        channel_value++;
        ((SpriteFrameState *)record)->color.c.b = channel_value;
        ((SpriteFrameState *)record)->color.c.g = channel_value;
        ((SpriteFrameState *)record)->color.c.r = channel_value;
        low_word = ((SpriteFrameState *)record)->scale_x;
        word_or_frame += 0x10;
        ((SpriteFrameState *)record)->scale_y = word_or_frame;
        low_word += 0x100;
        ((SpriteFrameState *)record)->scale_x = low_word;
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

        channel_value = ((SpriteFrameState *)record)->color.c.b;
        low_word = ((SpriteFrameState *)record)->scale_x;
        channel_value++;
        low_word += 0x80;
        ((SpriteFrameState *)record)->color.c.b = channel_value;
        ((SpriteFrameState *)record)->color.c.g = channel_value;
        ((SpriteFrameState *)record)->color.c.r = channel_value;
        ((SpriteFrameState *)record)->scale_x = low_word;
        next_high_word = sequence->unk_02.s << 8;
        ((SpriteFrameState *)record)->scale_y = next_high_word;
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

        channel_value = ((SpriteFrameState *)record)->color.c.b + 6;
        ((SpriteFrameState *)record)->color.c.b = channel_value;
        ((SpriteFrameState *)record)->color.c.g = channel_value;
        ((SpriteFrameState *)record)->color.c.r = channel_value;
        word_or_frame = sequence->unk_02.s;

        next_high_word = (word_or_frame + 0x10) << 8;
        ((SpriteFrameState *)record)->scale_y = next_high_word;
        if (sequence->unk_02.s < sequence->unk_04) {
            return;
        }
        sequence->unk_02.u = 0;
        sequence->unk_00.u++;
        return;
    }
    case 3:
        func_800478B8(record);
        return;
    default:
        return;
    }
}

s32 create_randomized_transform_effect(s32 owner_id, Row_8189EBBC_S_800243BC_3 *transform)
{
    s32 random_value;
    s32 rounded_random;
    s32 return_value;
    SpriteFrameState *sprite;
    void *object;
    Row_8189EBBC_S_800243BC_1 *state;
    Row_8189EBBC_S_800243BC_4 *object_transform;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        ((Row_8189EBBC_S_800243BC_0 *)object)->unk_10 = &D_80024264;
        state->unk_08 = owner_id;
        ((Row_8189EBBC_S_800243BC_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        state->unk_04 = 0x10;
        sprite = ((Row_8189EBBC_S_800243BC_0 *)object)->unk_0C;
        sprite->clut = 0x7E02;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        sprite->scale_y = 0;
        sprite->scale_x = 0;
        sprite->flags = (s16)(sprite->flags | 0xC);
        sprite->tpage_abr = (u16)(sprite->tpage_abr | 0x20);
        sprite->flags = (u16)(sprite->flags | 0x100);
        random_value = rand();
        rounded_random = random_value;
        if (random_value < 0) {
            rounded_random = random_value + 0xF;
        }
        func_8003DB94(sprite, &D_800DEF08,
                      (s16)(random_value - ((rounded_random >> 4) * 0x10)));
        register_node(object, &transform_effect_tag);
        object_transform = ((Row_8189EBBC_S_800243BC_0 *)object)->unk_08;
        return_value = (s32)object;
        *object_transform = *(Row_8189EBBC_S_800243BC_4 *)transform;
        return return_value;
    }
    return 0;
}
