#include "dungeon/effect/shade/fading_effect_set.h"
#include "shared/sprite_frame_state.h"
void (*const dungeon_ovl_188898c_entry)(void) = (void (*)(void))move_linked_effect_along_path;

void func_80024060(s32 x, s32 y, void *kind, s32 flags) {
    u8 *actor = dungeon_actor_ring_anchor;
    x = (s16)x;
    y = (s16)y;
    flags = ((u8)flags >> 2) + 0x10;
    do {
        if ((s16)check_entity_interaction_compatibility(kind, actor) != 0) {
            u8 *header = *(u8 **)(actor - 0x14);
            if (abs(header[0x24] - x) < 3 && abs(header[0x25] - y) < 3 && (s16)check_entity_eligibility(actor) != 0) {
                s32 amount = flags + (generate_random_value() & 3);
                s32 mode = 0x10;
                if (current_spell_effect_variant == 0xFF) mode = 0xFF;
                try_apply_status_effect(actor, mode, amount);
            }
        }
        actor = *(u8 **)(actor + 0x5C) + 0x20;
    } while (actor != dungeon_actor_ring_anchor);
}

void advance_fading_effect(void *effect, void *position, void *render_data)
{
    u8 *effect_state = *(u8 **)effect;
    u16 coordinate;
    u8 intensity;

    *(u16 *)(effect_state + 0x14) = *(u16 *)(effect_state + 0x14) + 1;
    coordinate = *(u16 *)((u8 *)render_data + 0x1E);
    intensity = *(u8 *)((u8 *)render_data + 0xE);
    coordinate += 0x400;
    intensity -= 4;
    *(u16 *)((u8 *)render_data + 0x1E) = coordinate;
    *(u16 *)((u8 *)render_data + 0x1C) = coordinate;
    *(u8 *)((u8 *)render_data + 0xE) = intensity;
    *(u8 *)((u8 *)render_data + 0xD) = intensity;
    *(u8 *)((u8 *)render_data + 0xC) = intensity;
    if (intensity == 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
    *(u16 *)((u8 *)position + 0xA) -= 8;
    advance_sprite_animation_and_textures(render_data);
    if (*(u16 *)((u8 *)render_data + 0x14) & 0x6000) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void create_randomized_grayscale_effect(s32 user_data, ovl_188898c_81868A64_S_81868A64_3 *source_pos, u8 intensity) {
    SpriteFrameState *render_state;
    ovl_188898c_81868A64_S_81868A64_2 *effect_pos;
    ovl_188898c_81868A64_S_81868A64_0 *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        render_state = effect->unk_0C;
        effect->unk_10 = (void *)advance_fading_effect;
        effect->unk_20 = user_data;
        render_state->color.c.b = intensity;
        render_state->color.c.g = intensity;
        render_state->color.c.r = intensity;
        select_record_entry_and_value(render_state, &D_800DEDB0, 0);
        render_state->scale_y = 0x1800;
        render_state->scale_x = 0x1800;
        render_state->clut = 0x7E0B;
        render_state->tpage_abr = (u16) (render_state->tpage_abr | 0x60);
        render_state->flags = (u16) (render_state->flags | 0x10C);
        register_node(effect, project_sprite_chain);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (s16) ((source_pos->unk_0A + (rand() % 17)) - 8);
    }
}

void animate_spiral_grayscale_effect(void *effect, void *position) {
    s32 radial_product;
    s32 fade_angle;
    s32 grow_angle;
    s32 grow_point;
    s32 fade_angle_fixed;
    s32 grow_angle_fixed;
    u16 angular_speed;
    void *effect_data;
    s16 state;

    effect_data = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C;
    ((ovl_188898c_81868B84_S_81868B84_1 *)effect_data)->unk_14 = (u16) (((ovl_188898c_81868B84_S_81868B84_1 *)effect_data)->unk_14 + 1);
    ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s + 1);
    state = *(s16 *)effect;
    switch (state) {
    case 0:
        ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v =
            (u16) (((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v - 4);
        create_randomized_grayscale_effect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 1:
        grow_point = 0;
        grow_angle_fixed = grow_point;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 + 6);
        angular_speed = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A + 0x10;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A = angular_speed;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + angular_speed);
        do {
            grow_angle = grow_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + grow_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_0C.at02_u16.v + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + grow_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_10.at02_u16.v + (radial_product >> 8));
            if ((check_left_tile_and_center_height(((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v,
                ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v,
                (s16) ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v) << 0x10) == 0) {
                create_randomized_grayscale_effect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
            }
            grow_angle_fixed += 0x05550000;
            grow_point += 1;
        } while (grow_point < 3);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 0x20) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 2:
        grow_point = 0;
        fade_angle_fixed = grow_point;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 + 6);
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A);
        do {
            fade_angle = fade_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + fade_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_0C.at02_u16.v + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + fade_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_10.at02_u16.v + (radial_product >> 8));
            if ((check_left_tile_and_center_height(((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v,
                ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v,
                (s16) ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v) << 0x10) == 0) {
                create_randomized_grayscale_effect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
            }
            fade_angle_fixed += 0x05550000;
            grow_point += 1;
        } while (grow_point < 3);
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10 = (u8) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10 - 8);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 3:

        ((ovl_188898c_81868B84_S_81868B84_3 *)(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C))->unk_16 = 1;
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((ovl_188898c_81868B84_S_81868B84_0_pre *)effect)[-1].unk_00 | 0x8000);
        {
            ObjectFlagBlock *global_flags;
            global_flags = &object_flag_block;
            global_flags->flags |= 0x8000;
        }
        return;
    default:
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = 3;
    }
}

void create_coordinate_sprite_object(void *owner, ovl_188898c_81868E84_S_81868E84_3 *coords) {
    u32 owner_value;
    u16 x;
    u16 y;
    u16 z;
    void *object;
    ovl_188898c_81868E84_S_81868E84_1 *state;
    ovl_188898c_81868E84_S_81868E84_4 *coord_pairs;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_10 = (void *)animate_spiral_grayscale_effect;
        state = object + 0x20;
        ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        owner_value = ((ovl_188898c_81868E84_S_81868E84_2 *)owner)->unk_09;
        state->unk_06 = 0;
        state->unk_08 = 0;
        state->unk_0A = 0;
        state->unk_0C = owner;
        state->unk_10 = 0x40;
        state->unk_04 = owner_value;
        coord_pairs = ((ovl_188898c_81868E84_S_81868E84_0 *)object)->unk_08;
        x = coords->unk_02;
        coord_pairs->unk_0E = x;
        coord_pairs->unk_02 = x;
        y = coords->unk_06;
        coord_pairs->unk_12 = y;
        coord_pairs->unk_06 = y;
        z = coords->unk_0A;
        coord_pairs->unk_16 = z;
        coord_pairs->unk_0A = z;
    }
}

/* MECHANISM: Hold owner[9] in a u32 local after the first two zero stores.
   Its live range claims $a0, leaving the allocator result in $a1; u32 avoids
   the redundant andi and collapses the +1-word branch-displacement cascade. */

void shrink_and_brighten_effect(void *state_ref, void *unused, void *effect) {
    u16 scale;
    u8 brightness;
    void *state;

    state = *(void **)state_ref;
    *(u16 *)((u8 *)state + 0x14) = *(u16 *)((u8 *)state + 0x14) + 1;
    scale = *(u16 *)((u8 *)effect + 0x1E) - 0x400;
    brightness = *(u8 *)((u8 *)effect + 0xE) + 4;
    *(u16 *)((u8 *)effect + 0x1E) = scale;
    *(u16 *)((u8 *)effect + 0x1C) = scale;
    *(u8 *)((u8 *)effect + 0xE) = brightness;
    *(u8 *)((u8 *)effect + 0xD) = brightness;
    *(u8 *)((u8 *)effect + 0xC) = brightness;
    advance_sprite_animation_and_textures(effect);
    if (*(u16 *)((u8 *)effect + 0x14) & 0x6000) {
        *(s8 *)((u8 *)*(void **)state_ref + 0x16) = 1;
        *(u16 *)((u8 *)state_ref - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void delay_and_fade_particle(s32 value, void *source_data) {
    ovl_188898c_81868FDC_Object *obj;
    SpriteFrameState *sprite;
    u16 *dst;
    u16 *src;

    obj = (ovl_188898c_81868FDC_Object *)allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->callback = (void *)shrink_and_brighten_effect;
        sprite = obj->sprite;
        obj->value = value;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, D_80025368, 0);
        sprite->scale_y = 0x4000;
        sprite->scale_x = 0x4000;
        sprite->clut = 0x7E0B;
        sprite->tpage_abr |= 0x60;
        sprite->flags |= 0x10C;
        register_node(obj, project_sprite_chain);
        dst = obj->dst;
        src = source_data;
        dst[1] = src[1];
        dst[3] = src[3];
        dst[5] = src[5];
    }
}

static __inline__ s32 first_delta_s32_s32(s32 end, s32 start)
{
    return end - start;
}

/* Interpolate and shade a line, project its endpoints, and add it to the ordering table. */
s32 interpolate_shade_and_queue_line(void *line_data, void *unused_render_context)
{
    u8 *line;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_work_a;
    void *projection_work_b;
    ovl_188898c_818690C8_PackedDelta coord_delta;
    s32 bit_mask;
    s32 index;
    s32 multiplier;
    u8 *line_bytes = line_data;
    s32 coord_y;
    s32 first_z;
    s32 second_z;
    s32 depth;
    s32 depth_sum;
    s32 result;
    u32 *ordering_table;
    u8 *render_ctx = *(u8 **)((u8 *)(&g_game_work));

    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((GpuContext *)render_ctx)->packetCursor;
    line = line_bytes;
    ((GpuContext *)render_ctx)->packetCursor = packet + 0x14;

    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at03.v = 4;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_07 = 0x50;

    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_1A;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_1E;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_22;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_32;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_36;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_3A;

    index = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 1;
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:

    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        coord_delta.word = first_delta_s32_s32(((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C,
            (x0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64)) << 16;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;

        y0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (coord_delta.word & mask) >> 16;
        coord_delta.half.high = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E - y0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C = x0 + step_x;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;

        end_z = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70;
        z0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68;
        step_y = coord_delta.half.high;
        coord_delta.half.high = end_z - z0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E = y0 + step_y;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;
        z0 += coord_delta.half.high;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70 = z0;
    }
        {
            s32 level;

            bit_mask = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10;
            multiplier = 15;
            level = bit_mask + 1;
            line = (u8 *)(level * multiplier);
            multiplier = 23;
            coord_y = level * multiplier;
            level = 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = level;
            level -= (7 - bit_mask) * 8;
            multiplier = (s32)line + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = multiplier;
            multiplier = coord_y + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = multiplier;
        }
        break;
    case 7:

        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = 0x7F;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = 0;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = 0xFF;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:

    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        coord_delta.word = first_delta_s32_s32(((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C,
            (x0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64)) << 16;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;

        y0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (coord_delta.word & mask) >> 16;
        coord_delta.half.high = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E - y0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64 = x0 + step_x;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;

        end_z = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70;
        z0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68;
        step_y = coord_delta.half.high;
        coord_delta.half.high = end_z - z0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66 = y0 + step_y;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;
        z0 += coord_delta.half.high;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68 = z0;
    }
        {
            s32 k;
            s32 k23;

            coord_y = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10;
            k = 15;
            bit_mask = coord_y - 7;
            line = (u8 *)(bit_mask * k);
            k23 = 23;
            bit_mask *= k23;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = 0;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = (k - coord_y) * 8;
            multiplier = 0x7F;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = multiplier;
            multiplier = 0xFF;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = multiplier;
            multiplier = (s32)line + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = multiplier;
            multiplier = bit_mask + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = multiplier;
        }
        break;
    }

    projection_work_a = scratch + 0x84;
    projection_work_b = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_work_a, projection_work_b);
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F4 = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_work_a, projection_work_b);
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F8 = second_z;

    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_08 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_D8;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0A = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DA;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_10 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DC;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_12 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DE;

    depth_sum = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F4;
    depth_sum += ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F8;
    depth = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_B4 = depth;
    if ((u32)depth < 0x1E0U) {
        u32 entry_addr;
        u32 *ot_base;
        s32 low_mask;
        low_mask = 0x00FFFFFF;
        entry_addr = depth << 2;
        ot_base = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18;
        depth = 0xFF000000;
        entry_addr += (u32)ot_base;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at00.v =
            (((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at00.v & depth) |
            (*(u32 *)entry_addr & low_mask);

        index = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_B4;
        ordering_table = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18;
        ordering_table[index] =
            (ordering_table[index] & depth) |
            ((u32)packet & low_mask);
    }

    result = 0;
    return result;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Each interpolation arm keeps its coordinates, steps and mask in arm-local variables
   (single-lifetime quantities for local-alloc), while coord_delta and line stay function-wide;
   the masked step_x read gives the mask the extra reference that orders it ahead of y0. */

void move_linked_effect_along_path(ovl_188898c_818694D4_Controller *input_ctrl, ovl_188898c_818694D4_Motion *input_motion, void *input_render_data)
{
    u8 *root;
    void *render_data;
    ovl_188898c_818694D4_RootPrefix *root_prefix;
    ovl_188898c_818694D4_Lookup *lookup;
    ovl_188898c_818694D4_Lookup *lookup_2;
    ovl_188898c_818694D4_Motion *source_motion;
    ovl_188898c_818694D4_Motion *linked_motion;
    u8 *linked_root;
    u8 *linked_root_2;
    u8 *linked_root_3;
    s16 offsets[3];
    u16 end_x;
    u16 end_y;
    s32 steps;
    s32 coord_diff;
    s32 origin_coord;
    s32 floor_height;
    u16 cell_x;
    u16 cell_y;
    u16 source_z;
    s32 state;
    u32 elapsed;

    elapsed = (u16)input_ctrl->timer;
    state = input_ctrl->state;
    root = input_ctrl->root;
    input_ctrl->timer = elapsed + 1;
    render_data = input_render_data;
    switch (state) {
    case 0:
        input_ctrl->timer = 0;
        input_ctrl->state++;
        input_ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        input_ctrl->ready = 0;
        ((s32 *)render_data)[3] = 0x00808080;

    case 1:
        root_prefix = (ovl_188898c_818694D4_RootPrefix *)(root - 0x20);
        if (resolve_record_orientation_or_fallback(root_prefix->lookup->key, root_prefix->lookup, offsets, 0) == 0) {
            if (!(root_prefix->lookup->flags & 0x8000)) {
                break;
            }
        }

        source_motion = root_prefix->motion;
        input_motion->x.h.hi = source_motion->x.h.hi;
        input_motion->y.h.hi = source_motion->y.h.hi;
        source_z = source_motion->z.h.hi;
        input_motion->z.h.hi = source_z;
        if (!(root_prefix->lookup->flags & 0x8000)) {
            input_motion->x.h.hi += offsets[0];
            input_motion->y.h.hi += offsets[1];
            input_motion->z.h.hi += offsets[2];
        } else {
            input_motion->z.h.hi = source_z - 64;
        }
        if (!(*input_ctrl->flags & 0x80)) {
            break;
        }

        input_ctrl->saved = *input_motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            linked_motion = *(ovl_188898c_818694D4_Motion **)(linked_root - 0x18);

            origin_coord = input_motion->x.h.hi;
            offsets[0] = abs(linked_motion->x.h.hi - origin_coord);

            offsets[1] = abs(linked_motion->y.h.hi - input_motion->y.h.hi);

            linked_root_2 = *(u8 **)(root + 0x60);
            origin_coord = input_motion->z.h.hi;
            offsets[2] = abs(*(s16 *)(linked_root_2 + 0x88) - origin_coord);

            linked_root_3 = *(u8 **)(root + 0x60);
            lookup = *(ovl_188898c_818694D4_Lookup **)(linked_root_3 - 0x14);
            input_ctrl->cell_x = lookup->cell_x;
            input_ctrl->cell_y = lookup->cell_y;

            input_ctrl->target[0].val = linked_motion->x.val;
            input_ctrl->target[1].val = linked_motion->y.val;
            coord_diff = *(u16 *)(*(u8 **)(root + 0x60) + 0x88);
            input_ctrl->target[2].h.lo = 0;
            input_ctrl->target[2].h.hi = coord_diff;

            input_motion->dx.val = (input_ctrl->target[0].val - input_motion->x.val) / 15;
            input_motion->dy.val = (input_ctrl->target[1].val - input_motion->y.val) / 15;
            input_motion->dz.val = (input_ctrl->target[2].val - input_motion->z.val) / 15;
            input_ctrl->timer = 0;
            input_ctrl->state++;
            break;
        }

        steps = 0;
        lookup_2 = root_prefix->lookup;
        cell_x = lookup_2->cell_x;
        cell_y = lookup_2->cell_y;
        end_x = cell_x;
        end_y = cell_y;

        do {
            if ((s16)check_layer_offset_height(((s16)cell_x << 6) & 0xFFC0,
                ((s16)cell_y << 6) & 0xFFC0,
                *(s16 *)(root + 0x88),
                (s16)(input_ctrl->angle << 9)) != 0) {
                break;
            }

            {
                s16 *step_x;
                s16 *step_y;
                s32 height;
                s32 direction;
                u16 root_z;

                direction = (s16)input_ctrl->angle;
                root_z = *(u16 *)(root + 0x88);
                lookup = &dir_step_x[direction];
                step_x = lookup;
                height = (s16)(root_z - 32);
                step_y = &dir_step_y[direction];
                floor_height = sample_terrain_surface_height((((s16)cell_x + *step_x) << 6) + 32 & 0xFFE0,
                    (((s16)cell_y + *step_y) << 6) + 32 & 0xFFE0,
                    height);
            }
            if ((s16)floor_height >= 513) {
                break;
            }
            if ((s16)(floor_height - *(u16 *)(root + 0x88)) < -63) {
                break;
            }

            {
                s32 direction;

                direction = (s16)input_ctrl->angle;
                steps++;
                cell_x += dir_step_x[direction];
                cell_y += dir_step_y[direction];
                end_x = cell_x;
                end_y = cell_y;
            }
        } while (steps < 8);

        {

            linked_motion = (ovl_188898c_818694D4_Motion *)input_ctrl->target;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].val = 0;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].val = 0;
            input_ctrl->target[0].val = 0;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[0].h.hi = ((end_x << 16) >> 10) + 32;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].h.hi = ((end_y << 16) >> 10) + 32;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = -1024;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = sample_terrain_surface_height((u16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[0].h.hi,
                (u16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].h.hi, -1024);
            if ((s16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi >= 513) {
                ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = input_motion->z.h.hi + 32;
            }
        }

        input_motion->dx.val = (input_ctrl->target[0].val - input_motion->x.val) / 15;
        input_motion->dy.val = (input_ctrl->target[1].val - input_motion->y.val) / 15;
        input_motion->dz.val = (input_ctrl->target[2].val - input_motion->z.val) / 15;
        input_ctrl->cell_x = end_x;
        input_ctrl->cell_y = end_y;
        goto advance;

    case 2:
        input_motion->x.val += input_motion->dx.val;
        input_motion->y.val += input_motion->dy.val;
        input_motion->z.val += input_motion->dz.val;
        interpolate_shade_and_queue_line(input_ctrl, render_data);
        if (input_ctrl->timer < 15) {
            break;
        }
        input_ctrl->timer = 0;
        input_ctrl->state++;
        delay_and_fade_particle(input_ctrl, input_motion);
        play_sound_if_enabled(0x300);
        break;

    case 3:
        if (input_ctrl->ready == 0) {
            break;
        }
        input_ctrl->timer = 0;
        input_ctrl->ready = 0;
        input_ctrl->state++;
        create_coordinate_sprite_object(input_ctrl, input_motion);
        break;

    case 4:
        if (input_ctrl->ready == 0) {
            break;
        }
        func_80024060(input_ctrl->cell_x, input_ctrl->cell_y, root, input_ctrl->kind);

advance:
        input_ctrl->timer = 0;
        input_ctrl->state++;
        break;

    case 5:
        if (input_ctrl->active == 0) {
            g_dungeon_status.active_actor = 0;
            *(u16 *)((u8 *)input_ctrl - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }

    default:
        break;
    }

    input_ctrl->active = 0;
}
