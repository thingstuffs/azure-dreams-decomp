#include "modules/dungeon_ovl_7e71d800.h"

s32 func_80024C7C(void *node_data) {
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
        global_base = &gameWork;
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
                            void *context = global_base->unk_000;
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
                            void *context = global_base->unk_000;
                            ((Row_818E747C_S_80024C7C_3 *)primitive)->unk_00.s = (s32)(
                                (((Row_818E747C_S_80024C7C_3 *)primitive)->unk_00.u & 0xFF000000) |
                                (((Row_818E747C_S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 &
                                 address_mask));
                        }
                        segment_start--;
                        {
                            void *context = global_base->unk_000;
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
