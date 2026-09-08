#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024C7C_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2E];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x3];
    u16 unk_4A;
} S_80024C7C_0;   /* node in func_80024C7C */

typedef struct S_80024C7C_1 {
    void * unk_00;
} S_80024C7C_1;   /* global_base in func_80024C7C */

typedef struct S_80024C7C_2 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80024C7C_2;   /* context in func_80024C7C */

typedef struct S_80024C7C_3 {
    union { s32 s; u32 u; } unk_00;   /* accessed as both */
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    u8 unk_15;
    s16 unk_16;
    s16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    s16 unk_20;
    u16 unk_22;
    s8 unk_24;
    s8 unk_25;
} S_80024C7C_3;   /* entry in func_80024C7C */

typedef struct S_80024C7C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024C7C_4;   /* (u8 *)transform_base + lo in func_80024C7C */

typedef struct S_80024C7C_5 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_80024C7C_5;   /* (u8 *)(height4 + (u32)context) in func_80024C7C */

typedef struct S_80024C7C_6_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80024C7C_6_pre;   /* the 0x8 bytes before arg0 in func_80024C7C, addressed as arg0[-1] */



extern void func_80065770();
extern s32 func_80069EF8();
extern s32 func_800666F4();
extern s32 func_80066640();
extern s16 func_80066460();
extern s16 func_8006649C();
extern u8 D_80083160[];

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Point3;

typedef struct {
    s16 x;
    s16 y;
} Point2;

/* Draw four jittered textured strips for each node in the linked list. */
s32 func_80024C7C(void *node_data) {
    for (;;) {
        Point3 world_points[5];
        s16 depths[8];
        s16 scratch[8];
        s16 projection_aux[8];
        Point2 screen_points[6];
        Point2 strip_points[5];
        Point2 *screen_base;
        Point2 *strip_base;
        Point2 *corner;
        Point2 *jitter_corner;
        Point2 *jitter_point;
        Point2 *segment_start;
        u8 *node;
        u8 *global_base;
        s32 corner_index;
        s32 segment_index;
        s32 step;
        s32 depth_bucket;
        s32 ot_offset;
        u32 address_mask;
        Point3 *world_base;
        s32 corner_offset;
        void *next_node;

        node = node_data;
        global_base = D_80083160;
        world_base = world_points;
        screen_base = screen_points;
        strip_base = strip_points;

        world_points[4].x = (s16)(((S_80024C7C_0 *)node)->unk_0C + 0x20);
        world_points[4].y = (s16)(((S_80024C7C_0 *)node)->unk_0E + 0x20);
        world_points[4].z = ((S_80024C7C_0 *)node)->unk_10.s;
        for (corner_index = 3; corner_index >= 0; corner_index--) {
            world_base[corner_index].x = (s16)(((S_80024C7C_0 *)node)->unk_0C +
                                    ((corner_index >> 1) << 6));
            world_base[corner_index].y = (s16)(((S_80024C7C_0 *)node)->unk_0E +
                                    ((corner_index % 2) << 6));
            world_base[corner_index].z = (s16)(((S_80024C7C_0 *)node)->unk_10.u +
                                    ((S_80024C7C_0 *)node)->unk_4A);
        }
        func_80065770(world_points, screen_points, depths, scratch, projection_aux, 5);

        strip_points[0] = screen_points[4];
        address_mask = 0x00FFFFFF;
        corner_offset = 12;
        corner = &screen_base[3];

        for (corner_index = 3; corner_index >= 0; corner_index--) {
            depth_bucket = ((s32)depths[4] + depths[corner_index]) >> 3;
            if ((u32)depth_bucket < 0x1E0U) {
                Point2 *segment_end;

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
                        s32 half_step;
                        s16 corner_x;

                        jitter_point->y = (s16)((u16)screen_points[4].y +
                                                row_offset);
                        x_jitter = func_80069EF8() % step;
                        segment_index--;
                        row_offset -= step;
                        corner_x = jitter_corner->x;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        half_step = step >> 1;
                        ASM_KEEP(half_step);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
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
                        register u32 primitive_color ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                        {
                            void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                            primitive = ((S_80024C7C_2 *)context)->unk_8D0;
                            ((S_80024C7C_2 *)context)->unk_8D0 =
                                (void *)((u8 *)primitive + 0x34);
                        }
                        primitive_color = 0x00808080;
                        ((S_80024C7C_3 *)primitive)->unk_04 = primitive_color;
                        func_800666F4(primitive, primitive_color);
                        func_80066640(primitive, 1);
                        ((S_80024C7C_3 *)primitive)->unk_16 =
                            func_80066460(0, 1, 0x2C0, 0x100);
                        ((S_80024C7C_3 *)primitive)->unk_0E = func_8006649C(0xA0, 0x1F7);

                        vertex_y = segment_start->y;
                        ((S_80024C7C_3 *)primitive)->unk_1A = (u16)vertex_y;
                        ((S_80024C7C_3 *)primitive)->unk_0A = (u16)vertex_y;
                        next_index = segment_index + 1;
                        segment_end = &strip_base[next_index];
                        vertex_y = segment_end->y;
                        ((S_80024C7C_3 *)primitive)->unk_22 = (u16)vertex_y;
                        ((S_80024C7C_3 *)primitive)->unk_12 = (u16)vertex_y;

                        step = ((s32)((S_80024C7C_4 *)((u8 *)screen_base + screen_offset))->unk_02 -
                                      (s32)screen_points[4].y) >> 4;
                        if (step == 0) {
                            step = 1;
                        }
                        ((S_80024C7C_3 *)primitive)->unk_08 =
                            (u16)(segment_start->x - step);
                        ((S_80024C7C_3 *)primitive)->unk_10 =
                            (u16)(segment_end->x - step);
                        ((S_80024C7C_3 *)primitive)->unk_18 =
                            (s16)(((S_80024C7C_3 *)primitive)->unk_08 + step);
                        ((S_80024C7C_3 *)primitive)->unk_20 =
                            (s16)(((S_80024C7C_3 *)primitive)->unk_10 + step);

                        tex_coord = ((S_80024C7C_0 *)node)->unk_40;
                        ((S_80024C7C_3 *)primitive)->unk_1C = (u8)tex_coord;
                        ((S_80024C7C_3 *)primitive)->unk_0C = (u8)tex_coord;
                        tex_coord = (s16)(tex_coord + ((S_80024C7C_0 *)node)->unk_44);
                        ((S_80024C7C_3 *)primitive)->unk_24 = (s8)tex_coord;
                        ((S_80024C7C_3 *)primitive)->unk_14 = (s8)tex_coord;
                        tex_coord = ((S_80024C7C_0 *)node)->unk_42;
                        ((S_80024C7C_3 *)primitive)->unk_15 = (u8)tex_coord;
                        ((S_80024C7C_3 *)primitive)->unk_0D = (u8)tex_coord;
                        tex_coord = (s16)(tex_coord + ((S_80024C7C_0 *)node)->unk_46);
                        ((S_80024C7C_3 *)primitive)->unk_25 = (s8)tex_coord;
                        ((S_80024C7C_3 *)primitive)->unk_1D = (s8)tex_coord;

                        {
                            void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                            ((S_80024C7C_3 *)primitive)->unk_00.s = (s32)(
                                (((S_80024C7C_3 *)primitive)->unk_00.u & 0xFF000000) |
                                (((S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 &
                                 address_mask));
                        }
                        segment_start--;
                        {
                            void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                            ((S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 = (u32)(
                                (((S_80024C7C_5 *)((u8 *)(ot_offset + (u32)context)))->unk_B0 &
                                 0xFF000000) |
                                ((u32)(u8 *)primitive & address_mask));
                        }
                    }
                }
            }
            corner--;
            corner_offset -= 4;
        }

        next_node = ((S_80024C7C_6_pre *)node_data)[-1].unk_00;
        if (next_node == NULL) {
            return 0;
        }
        node_data = (u8 *)next_node + 0x20;
    }
}
