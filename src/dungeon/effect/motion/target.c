/* Target-following sprite motion, timed texture changes, and jittered strip rendering. */
#include "dungeon/effect/motion/target.h"


/* Eases a sprite toward its moving target, advances its animation, and removes it after brightening. */
void move_effect_toward_target(void *motion, Row_818E71DC_S_800249DC_2 *position, Row_818E71DC_S_800249DC_3 *visual) {
    s32 current_x;
    s32 current_y;
    s32 current_z;
    s32 delta;
    u16 ticks_left;
    Row_818E71DC_S_800249DC_1 *owner;

    owner = ((Rec_func_800249DC_arg0 *)motion)->unk_00.at00_pv.v;
    owner->unk_10 =
        (s32)(owner->unk_10 | 0x8000);

    ticks_left = ((Rec_func_800249DC_arg0 *)motion)->unk_48 - 1;
    ((Rec_func_800249DC_arg0 *)motion)->unk_48 = ticks_left;
    if ((ticks_left << 16) > 0) {
        ((Rec_func_800249DC_arg0 *)motion)->unk_1C =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_1C + ((Rec_func_800249DC_arg0 *)motion)->unk_34);
        ((Rec_func_800249DC_arg0 *)motion)->unk_20 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_20 + ((Rec_func_800249DC_arg0 *)motion)->unk_38);
        ((Rec_func_800249DC_arg0 *)motion)->unk_24 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_24 + ((Rec_func_800249DC_arg0 *)motion)->unk_3C);
    }

    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_1C;
    current_x = position->unk_00;
    delta -= current_x;
    position->unk_00 =
        (s32)(current_x + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_20;
    current_y = position->unk_04;
    delta -= current_y;
    position->unk_04 =
        (s32)(current_y + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_24;
    current_z = position->unk_08;
    delta -= current_z;
    position->unk_08 =
        (s32)(current_z + (delta / 5));

    advance_sprite_animation_and_textures(visual);
    if (visual->unk_14 & 0x6000) {
        visual->unk_04 = 0;
        visual->unk_05 = 0;
    }

    if ((u8)visual->unk_0C.u8 >= 0x60U) {
        ((Row_818E71DC_S_800249DC_0_pre *)motion)[-1].unk_00 =
            (u16)(((Row_818E71DC_S_800249DC_0_pre *)motion)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | 0x8000);
        return;
    }

    visual->unk_0C.s32 += 0xC0C0C;
}

/* Grows a timed effect for four updates, cycles texture coordinates, and marks it for removal after 15
   ticks. */
void advance_effect_state_and_frame(void *effect)
{
    s32 state;
    u16 timer;
    u16 counter;
    void *object;

    object = *(void **)effect;
    S32_AT(object, 0x10) |= 0x8000;

    state = S16_AT(effect, 0x4C);
    timer = U16_AT(effect, 0x4E) + 1;
    U16_AT(effect, 0x4E) = timer;

    switch (state) {
    case 0:
        U16_AT(effect, 0x4E) = 0;
        U16_AT(effect, 0x48) = 0;
        S16_AT(effect, 0x46) = 0x1F;
        S16_AT(effect, 0x44) = 0x1F;
        U16_AT(effect, 0x4C)++;
                        /* fallthrough */
    case 1:
        counter = U16_AT(effect, 0x48) + 1;
        U16_AT(effect, 0x48) = counter;
        S16_AT(effect, 0x4A) = (s16)counter * 0x30;

        if (S16_AT(effect, 0x48) >= 4) {
            U16_AT(effect, 0x4C)++;
        }
        break;
    case 2:
        if ((s16)timer >= 0xF) {
            U16_AT(effect, -2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        break;
    }

    S16_AT(effect, 0x40) = ((U16_AT(effect, 0x4E) & 3) << 5) + 0x80;
    S16_AT(effect, 0x42) = ((s16)U16_AT(effect, 0x4E) >> 2) << 5;
}

/* Projects linked effects as four jittered strips of textured quads and queues them by depth. */
s32 render_linked_jittered_effect_strips(void *node_data) {
    for (;;) {
        Row_818E747C_Point3 world_points[5];
        s16 depths[8];
        s16 scratch[8];
        s16 projection_aux[8];
        Row_818E747C_Point2 screen_points[6];
        Row_818E747C_Point2 strip_points[5];
        Row_818E747C_Point2 *screen_base;
        Row_818E747C_Point2 *strip_base;
        Row_818E747C_Point2 *corner;
        Row_818E747C_Point2 *jitter_corner;
        Row_818E747C_Point2 *jitter_point;
        Row_818E747C_Point2 *segment_start;
        u8 *node;
        GameWork *global_base;
        s32 corner_index;
        s32 segment_index;
        s32 step;
        s32 depth_bucket;
        s32 ot_offset;
        u32 address_mask;
        Row_818E747C_Point3 *world_base;
        s32 corner_offset;
        void *next_node;

        node = node_data;
        global_base = &g_game_work;
        world_base = world_points;
        screen_base = screen_points;
        strip_base = strip_points;

        world_points[4].x = (s16)(((Row_818E747C_S_80024C7C_0 *)node)->unk_0C + 0x20);
        world_points[4].y = (s16)(((Row_818E747C_S_80024C7C_0 *)node)->unk_0E + 0x20);
        world_points[4].z = ((Row_818E747C_S_80024C7C_0 *)node)->unk_10.s;
        for (corner_index = 3; corner_index >= 0; corner_index--) {
            world_base[corner_index].x = (s16)(((Row_818E747C_S_80024C7C_0 *)node)->unk_0C +
                                    ((corner_index >> 1) << 6));
            world_base[corner_index].y = (s16)(((Row_818E747C_S_80024C7C_0 *)node)->unk_0E +
                                    ((corner_index % 2) << 6));
            world_base[corner_index].z = (s16)(((Row_818E747C_S_80024C7C_0 *)node)->unk_10.u +
                                    ((Row_818E747C_S_80024C7C_0 *)node)->unk_4A);
        }
        func_80065770(world_points, screen_points, depths, scratch, projection_aux, 5);

        strip_points[0] = screen_points[4];
        address_mask = 0x00FFFFFF;
        corner_offset = 12;
        corner = &screen_base[3];

        for (corner_index = 3; corner_index >= 0; corner_index--) {
            depth_bucket = ((s32)depths[4] + depths[corner_index]) >> 3;
            if ((u32)depth_bucket < 0x1E0U) {
                Row_818E747C_Point2 *segment_end;

                step = ((s32)corner->y - screen_points[4].y) >> 2;
                if (step == 0) {
                    step = 1;
                }
                segment_index = 4;
                jitter_corner = corner;
                jitter_point = &strip_base[4];
                {
                    s32 row_offset = step << 2;

                    do {
                        s32 x_jitter;
                        u32 half_step;
                        s16 corner_x;

                        jitter_point->y = (s16)((u16)screen_points[4].y +
                                                row_offset);
                        x_jitter = func_80069EF8() % step;
                        segment_index--;
                        row_offset -= step;
                        half_step = jitter_corner->x;
                        corner_x = half_step;
                        half_step = step >> 1;
                        jitter_point->x = (s16)(corner_x +
                                                x_jitter - half_step);
                        jitter_point--;
                    } while (segment_index > 0);
                }

                segment_index = 3;
                ot_offset = depth_bucket << 2;
                segment_start = &strip_base[3];
                {
                    s32 screen_offset = corner_offset;
                    for (; segment_index >= 0; segment_index--) {
                        s16 vertex_y;
                        s16 tex_coord;
                        s32 next_index;
                        void *primitive;
                        u32 primitive_color;

                        {
                            void *context = global_base->draw_buffer;
                            primitive = ((Row_818E747C_S_80024C7C_2 *)context)->unk_8D0;
                            ((Row_818E747C_S_80024C7C_2 *)context)->unk_8D0 =
                                (void *)((u8 *)primitive + 0x34);
                        }
                        primitive_color = 0x00808080;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_04 = primitive_color;
                        func_800666F4(primitive);
                        func_80066640(primitive, 1);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_16 =
                            func_80066460(0, 1, 0x2C0, 0x100);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_0E = func_8006649C(0xA0, 0x1F7);

                        vertex_y = segment_start->y;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_1A = (u16)vertex_y;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_0A = (u16)vertex_y;
                        next_index = segment_index + 1;
                        segment_end = &strip_base[next_index];
                        vertex_y = segment_end->y;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_22 = (u16)vertex_y;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_12 = (u16)vertex_y;

                        step = ((s32)((Row_818E747C_S_80024C7C_4 *)((u8 *)screen_base + screen_offset))->unk_02 -
                                      (s32)screen_points[4].y) >> 4;
                        if (step == 0) {
                            step = 1;
                        }
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_08 =
                            (u16)(segment_start->x - step);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_10 =
                            (u16)(segment_end->x - step);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_18 =
                            (s16)(((Row_818E747C_S_80024C7C_3 *)primitive)->unk_08 + step);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_20 =
                            (s16)(((Row_818E747C_S_80024C7C_3 *)primitive)->unk_10 + step);

                        tex_coord = ((Row_818E747C_S_80024C7C_0 *)node)->unk_40;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_1C = (u8)tex_coord;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_0C = (u8)tex_coord;
                        tex_coord = (s16)(tex_coord + ((Row_818E747C_S_80024C7C_0 *)node)->unk_44);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_24 = (s8)tex_coord;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_14 = (s8)tex_coord;
                        tex_coord = ((Row_818E747C_S_80024C7C_0 *)node)->unk_42;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_15 = (u8)tex_coord;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_0D = (u8)tex_coord;
                        tex_coord = (s16)(tex_coord + ((Row_818E747C_S_80024C7C_0 *)node)->unk_46);
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_25 = (s8)tex_coord;
                        ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_1D = (s8)tex_coord;

                        {
                            void *context = global_base->draw_buffer;
                            ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_00.s = (s32)(
                                (((Row_818E747C_S_80024C7C_3 *)primitive)->unk_00.u & 0xFF000000) |
                                (((Row_818E747C_S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 &
                                 address_mask));
                        }
                        segment_start--;
                        {
                            void *context = global_base->draw_buffer;
                            ((Row_818E747C_S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 = (u32)(
                                (((Row_818E747C_S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 &
                                 0xFF000000) |
                                ((u32)(u8 *)primitive & address_mask));
                        }
                    }
                }
            }
            corner--;
            corner_offset -= 4;
        }

        next_node = ((Row_818E747C_S_80024C7C_6_pre *)node_data)[-1].unk_00;
        if (next_node == NULL) {
            return 0;
        }
        node_data = (u8 *)next_node + 0x20;
    }
}

/* Copies one of six table pairs into the linked record's scale fields, defaulting to pair zero. */
void copy_selected_table_pair(void *record_field, s32 pair_index) {
    u16 value_pairs[12];
    s32 shifted_index;
    Row_818E786C_S_8002506C_1 *linked_record;
    Row_818E786C_S_8002506C_2 *pair;

    __builtin_memcpy(value_pairs, D_80024004, 24);
    if ((u32)(pair_index & 0xFFFF) >= 6U) {
        pair_index = 0;
    }
    shifted_index = pair_index << 0x10;
    pair = (u8 *)value_pairs + (shifted_index >> 0xE);
    linked_record = ((Row_818E786C_S_8002506C_0 *)((u8 *)record_field - 0x14))->unk_00;
    linked_record->unk_1C = (u16)pair->unk_00;
    linked_record->unk_1E = (u16)pair->unk_02;
}
