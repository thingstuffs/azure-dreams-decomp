#include "dungeon/effect/shade/update_directional_actor_effect.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/shade/update_directional_actor_effect.h"

void update_directional_actor_effect(s16 start_x, s16 start_y, s16 start_z, s16 end_x, s16 end_y,
                   s16 end_z, s16 *angles)
{
    struct Row_8194C81C_Delta delta;
    s32 divisor;

    delta.x = end_x - start_x;
    delta.y = end_y - start_y;
    delta.z = end_z - start_z;

    divisor = delta.z;
    if (divisor == 0) {
        divisor = 1;
    }
    angles[0] = -func_80065F90(delta.y, divisor);

    divisor = func_80064710(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    angles[1] = func_80065F90(delta.x, divisor);
    angles[2] = 0;
}

void update_homing_arc_and_brighten_effect(void *effect, void *motion, void *sprite)
{
    u16 offset[3];
    s32 state;

    state = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n;
    switch (state) {
    case 0:
        register_node((u8 *)effect - 0x20, project_sprite_chain);
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 + 1;
                        /* fall through */

    case 1:
    {
        void *source;
        source = ((Row_8194C8F0_S_800240F0_6 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_00))->unk_0C;
        if ((((Row_8194C8F0_S_800240F0_1 *)source)->unk_14 & 0x8000) ||
            resolve_record_orientation_or_fallback(((Row_8194C8F0_S_800240F0_1 *)source)->unk_08, source, offset, 0) != 0) {
            void *position;
            u16 source_z;

            position = ((Row_8194C8F0_S_800240F0_6 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_00))->unk_08;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at02.v = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_00.at02.v;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at02.v = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_04.at02.v;
            source_z = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_0A;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = source_z;

            if (!(((Row_8194C8F0_S_800240F0_1 *)source)->unk_14 & 0x8000)) {
                u16 offset_z;

                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at02.v += offset[0];
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at02.v += offset[1];
                offset_z = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v + offset[2];
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = offset_z;
            } else {
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = source_z - 0x20;
            }
        }
    }

        if (((Row_8194C8F0_S_800240F0_7 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_08))->unk_00 & 0x80) {
            u16 travel_frames;

            travel_frames = 10;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = travel_frames;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 += 1;
        }
        break;

    case 2:
    {
        u16 scale;
        scale = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E + 0x200;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1C = scale;
    }
        {
            void *position;
            position = ((Row_8194C8F0_S_800240F0_8 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_04))->unk_08;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_00.at00.v;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_04.at00.v;
        }
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 = (D_800814A8->unk_88 - 0x50) << 16;

        {
            s32 angle_index;
            angle_index = (g_game_work.view.camera_rotation.parts.viewAngle + D_800814A8->facing + 0x100) >> 7;
            if (resolve_record_orientation_or_fallback(*(void **)((angle_index & 0x1C) + (s32)(*(s32 * *)D_800E3D18)),
                              ((u8 *)(&D_80082E80)), offset, 0) != 0) {
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C += ((s16 *)offset)[0] << 16;
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 += ((s16 *)offset)[1] << 16;
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 += ((s16 *)offset)[2] << 16;
            }
        }

        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v) /
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v) /
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v) /
                ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s -
            (func_800644B8(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s * 0xAA) << 7);
        {
            u16 frames_left;
            frames_left = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u - 1;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = frames_left;
            if ((s16)frames_left > 0) {
                break;
            }
        }

        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14;
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = state;
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 += 1;
        break;

    case 3:
    {
        u16 scale;
        u8 brightness;
        scale = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E + 0x200;
        brightness = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0E + 8;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1C = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0E = brightness;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0D = brightness;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0C = brightness;
    }
        {
            u16 frames_left;
            frames_left = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u - 1;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = frames_left;
            if ((s16)frames_left > 0) {
                break;
            }
        }

        (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_12 = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_12 + 1;
}

void allocate_effect_and_initialize_sprite(s32 effect_data, s32 effect_param, s32 render_param)
{
    int color;
    void *effect;
    void *state;
    SpriteFrameState *sprite;
    effect = allocate_list_node(0x12, ((s32 *)&D_80083498.next));
    if (effect != 0) {
        *((s32 **) (((s8 *) effect) + 0x10)) = &D_800240F0;
        color = 0x80;
        state = effect + 0x20;
        *((s16 *) (((s8 *) state) + 0xC)) = 0;
        *((s16 *) (((s8 *) state) + 0xE)) = 0;
        *((s32 *) (((s8 *) effect) + 0x20)) = effect_data;
        *((s32 **) (((s8 *) state) + 4)) = ((s32 *)&D_80083498.next);
        *((s32 *) (((s8 *) state) + 8)) = effect_param;
        sprite = *((void **) (((s8 *) effect) + 0xC));
        sprite->color.c.b = color;
        sprite->color.c.g = color;
        sprite->color.c.r = color;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->clut = 0x7E00;
        sprite->source = render_param;
        sprite->tpage_abr = (u16) (sprite->tpage_abr | 0x20);
        sprite->flags = (u16) (sprite->flags | 0x10C);
    }
}

void update_rotating_effect_and_fade(void *effect, void *position, void *sprite) {
    Row_8194CD5C_InputVector local_offset;
    Row_8194CD5C_OutputVector rotated_offset;
    s32 y_product;
    u16 scale;
    u8 brightness;
    void *counter_state;

    counter_state = ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_00;
    ((Row_8194CD5C_S_8002455C_1 *)counter_state)->unk_1A = (u16) (((Row_8194CD5C_S_8002455C_1 *)counter_state)->unk_1A + 1);
    ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E = (u16) (((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E + 0x100);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_0C;
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_10;
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_14;
    local_offset.x = (s16) ((s32) ((func_800644B8((s16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E)
        >> 4) * ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2C) >> 8);
    y_product = (func_80064584((s16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E) >> 4) * ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2C;
    local_offset.z = 0;
    local_offset.y = (s16) (y_product >> 8);
    func_800649A0();
    func_80064B30(effect + 4, &local_offset, &rotated_offset);
    func_80064A40();
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at02.v + rotated_offset.x);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at02.v + rotated_offset.y);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at02.v + rotated_offset.z);
    if (((Row_8194CD5C_S_8002455C_0 *)effect)->unk_30 != 0) {
        ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_30 = 0U;
    }
    brightness = ((SpriteFrameState *)sprite)->color.c.b - 8;
    ((SpriteFrameState *)sprite)->color.c.b = brightness;
    ((SpriteFrameState *)sprite)->color.c.g = brightness;
    ((SpriteFrameState *)sprite)->color.c.r = brightness;
    if (!(brightness & 0xFF) || (scale = ((SpriteFrameState *)sprite)->scale_y - 0x100,
        ((SpriteFrameState *)sprite)->scale_y = scale, ((SpriteFrameState *)sprite)->scale_x = scale,
        ((SpriteFrameState *)sprite)->angle_z = (u16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E, func_800478B8(sprite),
        ((((SpriteFrameState *)sprite)->flags & 0x6000) != 0))) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((Row_8194CD5C_S_8002455C_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
/* MECHANISM: Two six-byte vector aggregates force stack slots sp+0x10..0x14 and sp+0x18..0x1C,
   restoring the 0x30 frame and the s0/s1/s2-only save set.
   cdk -G0 plus a direct scalar D_800814A0 RMW removes the extra address addiu and closes the residue. */

void create_textured_offset_object(void *source_object)
{
    s16 local_offset[3];
    u16 world_offset[3];
    s16 scale_component;
    s32 value;
    s32 word_x;
    s32 word_y;
    s32 word_z;
    u16 offset_length;
    u16 offset_angle;
    s32 *link;
    void *source = source_object;
    void *object;
    Row_8194CF00_S_80024700_0 *data;
    SpriteFrameState *primitive;
    void *primitive_2;
    s32 angle_or_zero;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        link = D_8002455C;
        (*(s32 * *)((u8 *)object + 0x10)) = link;
        value = (*(s32 *)((u8 *)source + 0));
        data = (u8 *)object + 0x20;
        (*(s32 *)((u8 *)object + 0x20)) = value;
        (*(Row_8194CF00_WordQuad *)((u8 *)object + 0x24)) = (*(Row_8194CF00_WordQuad *)((u8 *)source + 0x4C));
        (*(Row_8194CF00_WordQuad *)((u8 *)object + 0x34)) = (*(Row_8194CF00_WordQuad *)((u8 *)source + 0x5C));

        offset_length = (*(u16 *)((u8 *)source + 0x78));
        angle_or_zero = 0;
        data->unk_2C.u = offset_length;
        offset_angle = (*(u16 *)((u8 *)source + 0x76));
        data->unk_30 = 1;
        data->unk_2E.u = offset_angle;

        primitive = (*(void * *)((u8 *)object + 0xC));
        primitive->color.c.b = 0x40;
        primitive->color.c.g = 0x40;
        primitive->color.c.r = 0x40;
        func_8003DB94(primitive, D_800DE938, angle_or_zero);

        value = 0x2000;
        primitive->scale_y = value;
        primitive->scale_x = value;
        scale_component = data->unk_24;
        primitive->angle_x = scale_component >> 12;
        scale_component = data->unk_26;
        primitive->angle_y = scale_component >> 12;
        angle_or_zero = data->unk_2E.u;
        primitive->tpage_abr |= 0x20;
        primitive->flags |= 0xC;
        primitive->angle_z = angle_or_zero;
        register_node(object, project_sprite_chain);

        primitive_2 = (*(void * *)((u8 *)object + 8));
        word_x = (*(s32 *)((u8 *)source + 0x34));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_0C.at00u.v = word_x;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_00.at00.v = word_x;
        word_y = (*(s32 *)((u8 *)source + 0x38));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_10.s32 = word_y;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_04.at00.v = word_y;
        word_z = (*(s32 *)((u8 *)source + 0x3C));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_14.at00u.v = word_z;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_08.at00.v = word_z;

        local_offset[0] = ((func_800644B8(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        local_offset[1] = ((func_80064584(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        local_offset[2] = 0;
        func_800649A0();
        func_80064B30((u8 *)object + 0x24, local_offset, world_offset);
        func_80064A40();

        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_00.at02.v += world_offset[0];
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_04.at02.v += world_offset[1];
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_08.at02.v += world_offset[2];
    }
}

void advance_object_motion_and_animation(void *object) {
    s16 next_tick;
    s32 velocity_y;
    s32 velocity_z;
    s32 position_y;
    void *state;

    state = ((Row_8194D118_S_80024918_0 *)object)->unk_00;
    ((Row_8194D118_S_80024918_1 *)state)->unk_1A = ((Row_8194D118_S_80024918_1 *)state)->unk_1A + 1;
    ((Row_8194D118_S_80024918_0 *)object)->unk_78 = ((u32)func_800644B8(((Row_8194D118_S_80024918_0 *)object)->unk_74 << 8)) >> 6;
    velocity_y = ((Row_8194D118_S_80024918_0 *)object)->unk_44;
    ((Row_8194D118_S_80024918_0 *)object)->unk_34 += ((Row_8194D118_S_80024918_0 *)object)->unk_40;
    position_y = ((Row_8194D118_S_80024918_0 *)object)->unk_38;
    velocity_z = ((Row_8194D118_S_80024918_0 *)object)->unk_48;
    ((Row_8194D118_S_80024918_0 *)object)->unk_38 = position_y + velocity_y;
    ((Row_8194D118_S_80024918_0 *)object)->unk_3C += velocity_z;
    create_textured_offset_object(object);
    next_tick = (s16)((Row_8194D118_S_80024918_0 *)object)->unk_74 + 1;
    ((Row_8194D118_S_80024918_0 *)object)->unk_74 = next_tick;
    if (next_tick >= 9) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void allocate_effect_with_endpoints(s32 object_value, void *start_pos, void *end_pos, s16 setting, Row_8194D1E4_FourWords params_a,
    Row_8194D1E4_FourWords params_b, Row_8194D1E4_Packed8 packed_params) {
    s32 start_x;
    s32 start_y;
    s32 start_z;
    s32 word_0;
    s32 word_1;
    s32 word_2;
    s32 word_3;
    void *state;
    void *object;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        (*(s32 **)((u8 *)object + 0x10)) = &D_80024918;
        (*(s32 *)((u8 *)object + 0x20)) = object_value;
        ((Row_8194D1E4_S_800249E4_0 *)state)->unk_74 = 0;
        ((Row_8194D1E4_S_800249E4_0 *)state)->unk_76 = setting;
        start_x = (*(s32 *)((u8 *)start_pos + 0));
        (*(s32 *)((u8 *)state + 0x1C)) = start_x;
        (*(s32 *)((u8 *)state + 0x34)) = start_x;
        start_y = (*(s32 *)((u8 *)start_pos + 4));
        (*(s32 *)((u8 *)state + 0x20)) = start_y;
        (*(s32 *)((u8 *)state + 0x38)) = start_y;
        start_z = (*(s32 *)((u8 *)start_pos + 8));
        (*(s32 *)((u8 *)state + 0x24)) = start_z;
        (*(s32 *)((u8 *)state + 0x3C)) = start_z;
        (*(s32 *)((u8 *)state + 4)) = (s32) (*(s32 *)((u8 *)end_pos + 0));
        (*(s32 *)((u8 *)state + 8)) = (s32) (*(s32 *)((u8 *)end_pos + 4));
        (*(s32 *)((u8 *)state + 0xC)) = (s32) (*(s32 *)((u8 *)end_pos + 8));
        (*(s32 *)((u8 *)state + 0x40)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 0)) - (*(s32 *)((u8 *)start_pos + 0)))
            >> 3);
        (*(s32 *)((u8 *)state + 0x44)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 4)) - (*(s32 *)((u8 *)start_pos + 4)))
            >> 3);
        (*(s32 *)((u8 *)state + 0x48)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 8)) - (*(s32 *)((u8 *)start_pos + 8)))
            >> 3);
        word_0 = params_a.words[0];
        word_1 = params_a.words[1];
        word_2 = params_a.words[2];
        word_3 = params_a.words[3];
        (*(s32 *)((u8 *)object + 0x6C)) = word_0;
        (*(s32 *)((u8 *)object + 0x70)) = word_1;
        (*(s32 *)((u8 *)object + 0x74)) = word_2;
        (*(s32 *)((u8 *)object + 0x78)) = word_3;
        word_0 = params_b.words[0];
        word_1 = params_b.words[1];
        word_2 = params_b.words[2];
        word_3 = params_b.words[3];
        (*(s32 *)((u8 *)object + 0x7C)) = word_0;
        (*(s32 *)((u8 *)object + 0x80)) = word_1;
        (*(s32 *)((u8 *)object + 0x84)) = word_2;
        (*(s32 *)((u8 *)object + 0x88)) = word_3;
        *(Row_8194D1E4_Packed8 *)((u8 *)object + 0x8C) = packed_params;
    }
}

/* MECHANISM: Two 16-byte plus one packed 8-byte by-value args preserve the 0x28/s0-s3 hold set.
   Scalarized copy bursts color through v0,v1,a0,a1 while the allocation result is held in a2.
   A derived sp base with ASM_KEEP prevents packed tail loads folding from lwl/lwr pairs into lw;
   the paired tail source reads then also eliminate both downstream branch-displacement drifts. */

void update_three_way_target_effect(void *effect_arg, void *position) {
    s32 fallback_pos[6];
    Row_8194D1E4_Packed8 direction;
    Row_8194D1E4_FourWords transform[2];
    s16 offset[3];
    s32 *target_pos;
    TileObject *tile_or_y_steps;
    s32 *effect_pool;
    EntityRec *origin;

    s16 phase;
    s32 state_or_heading;
    s32 rounded_phase;
    s32 phase_random;
    s32 step_count;
    u16 *input_page;
    s32 position_valid;
    s32 origin_x, shifted_height, view_heading;
    s32 clear_tint_mask;
    s32 neutral_color;
    u16 start_delay;
    u16 ground_height;
    u16 near_height;
    u16 tint_delay;
    u16 next_state_c1;
    u16 next_state_c2;
    u16 next_state_c3;
    s32 forward_dx;
    s32 forward_dy;
    s32 backtrack_dx;
    s32 backtrack_dy;
    u8 tile_y;
    void *actor_or_frame;
    void *effect_data;
    s32 offset_mode;
    void *target;
    EntityRec *actor_value;
    void *actor_value_2;

    state_or_heading = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s;
    ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 = (u16)(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 + 1);
    switch ((u32)state_or_heading) {
    case 0:
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 = 0U;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s++;
        D_800814A8->unk_F4 = 0;
        allocate_effect_and_initialize_sprite(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_00 - 0x20, ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_04, &D_800DE5DC);
    case 1:
        if (*((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_04 & 0x80) {
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = 0xAU;
            ((Row_8194D354_S_80024B54_1 *)D_800814A8)->unk_A6--;
            D_800814A8->unk_A8 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_08;
            next_state_c1 = ((u16)D_800814A8->facing);
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s++;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0E = next_state_c1;
            if (func_80053EF0(4) != 2) {
                play_sound_if_enabled(0x300);
                ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
                return;
            }
            play_sound_if_enabled(0x4300);
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
            return;
        }
        break;
    case 2:
        start_delay = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 - 1;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = start_delay;
        if ((start_delay << 0x10) > 0) {
            break;
        }
        phase_random = func_80069EF8();
        rounded_phase = phase_random;
        if ((phase_random) < 0) {
            rounded_phase = (phase_random) + 0xFFF;
        }
        origin = &D_80083780;
        origin_x = (s32)D_80083780.x.v;
        (*(s32 *)((u8 *)position + 0)) = origin_x;
        phase = phase_random - ((rounded_phase >> 12) << 12);
        (*(s32 *)((u8 *)position + 4)) = origin->y.v;
        actor_value = D_800814A8;
        tile_or_y_steps = &D_80082E80;
        shifted_height = ((actor_value->unk_88) - 0x50) << 0x10;
        effect_data = offset;
        (*(s32 *)((u8 *)position + 8)) = shifted_height;
        view_heading = g_game_work.view.camera_rotation.parts.viewAngle;
        state_or_heading = actor_value->facing;
        offset_mode = 0;
        view_heading += state_or_heading;
        view_heading += 0x100;
        view_heading >>= 7;
        view_heading &= 0x1C;
        state_or_heading = (*(s32 *)D_800E3D18);
        actor_or_frame = (void *)(s32)*(s32 *)(view_heading + state_or_heading);
        if (resolve_record_orientation_or_fallback(actor_or_frame, tile_or_y_steps, effect_data, offset_mode) != 0) {
            (*(s32 *)((u8 *)position + 0)) = (s32)((*(s32 *)((u8 *)position + 0)) + (offset[0] << 0x10));
            (*(s32 *)((u8 *)position + 4)) = (s32)((*(s32 *)((u8 *)position + 4)) + (offset[1] << 0x10));
            (*(s32 *)((u8 *)position + 8)) = (s32)((*(s32 *)((u8 *)position + 8)) + (offset[2] << 0x10));
        }
        actor_or_frame = D_800814A8;
        target = scan_monster_along_heading(actor_or_frame, tile_or_y_steps->tile_position.parts.tile_x,
            tile_or_y_steps->tile_position.parts.tile_y, (s16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A, 8);
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14 = target;
        if (target != NULL) {
            target_pos = ((Row_8194D354_S_80024B54_6_pre *)target)[-1].unk_00;
        } else {
            target_pos = fallback_pos;
            step_count = 0;
            ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)((tile_or_y_steps->tile_position.parts.tile_x << 6) + 0x20);
            tile_y = tile_or_y_steps->tile_position.parts.tile_y;
            ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)((tile_y << 6) + 0x20);
            do {
                actor_or_frame = D_800814A8;
                forward_dx = dir_step_x[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u + (forward_dx << 6));
                forward_dy = dir_step_y[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u + (forward_dy << 6));
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_88;
                ground_height = get_surface_height_at_record(target_pos);
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = ground_height;
                if ((s16)ground_height > 0x200) {
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u =
                        (u16)((u16)D_800814A8->unk_88);
                }
                position_valid = check_left_tile_and_center_height(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u,
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u, (s16)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u);
                if ((position_valid << 0x10) != 0) {
                    actor_or_frame = D_800814A8;
                    backtrack_dx = dir_step_x[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u - (backtrack_dx
                        << 5));
                    backtrack_dy = dir_step_y[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u - (backtrack_dy
                        << 5));
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_88;
                    near_height = get_surface_height_at_record(target_pos);
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = near_height;
                    if ((s16)near_height > 0x200) {
                        ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u =
                            (u16)((u16)D_800814A8->unk_88);
                    }
                    break;
                }
                step_count += 1;
            } while (step_count < 8);
        }
        update_directional_actor_effect(((Row_8194D354_S_80024B54_8 *)position)->unk_02, ((Row_8194D354_S_80024B54_8 *)position)->unk_06,
            ((Row_8194D354_S_80024B54_8 *)position)->unk_0A, ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.s,
            (s32)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.s, (s32)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.s, &direction);
        func_80065820(&direction, transform);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, phase, transform[0], transform[1], direction);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, (s16)(phase + 0x555), transform[0], transform[1], direction);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, (s16)(phase + 0xAAA), transform[0], transform[1], direction);
        next_state_c2 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.u;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = 0x18U;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s = (s16)(next_state_c2 + 1);
        break;
    case 3:
        actor_or_frame = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14;
        if (actor_or_frame != NULL) {
            (*(s32 *)((u8 *)actor_or_frame + 0x1C)) = (s32)((*(s32 *)((u8 *)actor_or_frame + 0x1C)) | 0x10000000);
            effect_data = ((Row_8194D354_S_80024B54_13_pre *)(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14))[-1].unk_00;
            if ((s16)((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 >= 0xC) {
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C + 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D - 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E - 8);
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C >= 0xE1U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = 0xE0U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D < 0x20U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = 0x20U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E < 0x20U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = 0x20U;
                }
                input_page = (u16 *)0x80080000;
            } else {
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C - 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D + 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E + 8);
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C < 0x80U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = 0x80U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D >= 0x81U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = 0x80U;
                }
                input_page = (u16 *)(u32)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E;
                if ((u32)input_page >= 0x81U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = 0x80U;
                }
                input_page = (u16 *)0x80080000;
            }
        } else {
            input_page = (u16 *)0x80080000;
        }
        if (!(((Row_8194D354_S_80024B54_10 *)input_page)->unk_2E94 & 0x8000)) {
            tint_delay = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 - 1;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = tint_delay;
            if ((s16)tint_delay >= 0) {
                break;
            }
        }
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14 != NULL) {
            apply_attack_power_and_element_effects(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14, 0xA, ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_09, 9,
                (s32)(s16)((((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0E << 9) + 0x800), ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_00, 1);
            clear_tint_mask = 0xEFFFFFFF;
            neutral_color = 0x00808080;
            actor_value_2 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14;
            ((Row_8194D354_S_80024B54_1 *)actor_value_2)->unk_1C = (s32)(((Row_8194D354_S_80024B54_1 *)actor_value_2)->unk_1C & clear_tint_mask);
            effect_data = ((Row_8194D354_S_80024B54_1_pre *)actor_value_2)[-1].unk_00;
            (*(s32 *)((u8 *)effect_data + 0xC)) = neutral_color;
        }
        effect_pool = (s32 *)0x80080000;
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A != 0) {
            next_state_c3 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.u;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s = (s16)(next_state_c3 + 1);
            break;
        }
    case 4:
        effect_pool = (s32 *)0x80080000;
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A != 0) {
            break;
        }
        effect_pool = (s32 *)((u8 *)effect_pool + 0x3460);
        (*(s32 *)((u8 *)effect_pool + 0xC)) = 0;
        ((Row_8194D354_S_80024B54_11 *)effect_pool)->unk_0A = (u16)(((Row_8194D354_S_80024B54_11 *)effect_pool)->unk_0A - 1);
        (*(u16 *)((u8 *)effect_arg + -2)) = (u16)(((Row_8194D354_S_80024B54_0_pre *)effect_arg)[-1].unk_00 | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32)((*(s32 *)((u8 *)(&object_flag_block.flags) + 0)) | 0x8000);
        return;
    default:
        break;
    }
    ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
    return;
}
