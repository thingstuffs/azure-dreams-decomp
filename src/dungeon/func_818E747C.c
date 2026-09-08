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

s32 func_80024C7C(void *arg0) {
    for (;;) {
        Point3 points[5];
        s16 center[8];
        s16 scratch[8];
        s16 objects[8];
        Point2 transform[6];
        Point2 object_points[5];
        Point2 *transform_base;
        Point2 *object_points_base;
        Point2 *point;
        Point2 *point_for_x;
        Point2 *object_point;
        Point2 *object_point2;
        u8 *node;
        u8 *global_base;
        s32 layer;
        s32 object_index;
        s32 step;
        s32 height;
        s32 height4;
        u32 color_mask;
        Point3 *points_base;
        s32 layer_off;
        void *next_node;

        node = arg0;
        global_base = D_80083160;
        points_base = points;
        transform_base = transform;
        object_points_base = object_points;

        points[4].x = (s16)(((S_80024C7C_0 *)node)->unk_0C + 0x20);
        points[4].y = (s16)(((S_80024C7C_0 *)node)->unk_0E + 0x20);
        points[4].z = ((S_80024C7C_0 *)node)->unk_10.s;
        for (layer = 3; layer >= 0; layer--) {
            points_base[layer].x = (s16)(((S_80024C7C_0 *)node)->unk_0C +
                                    ((layer >> 1) << 6));
            points_base[layer].y = (s16)(((S_80024C7C_0 *)node)->unk_0E +
                                    ((layer % 2) << 6));
            points_base[layer].z = (s16)(((S_80024C7C_0 *)node)->unk_10.u +
                                    ((S_80024C7C_0 *)node)->unk_4A);
        }
        func_80065770(points, transform, center, scratch, objects, 5);

        object_points[0] = transform[4];
        color_mask = 0x00FFFFFF;
        layer_off = 12;
        point = &transform_base[3];

        for (layer = 3; layer >= 0; layer--) {
            height = ((s32)center[4] + center[layer]) >> 3;
            if ((u32)height < 0x1E0U) {
                Point2 *next_point;

                step = ((s32)point->y - transform[4].y) >> 2;
                if (step == 0) {
                    step = 1;
                }
                object_index = 4;
                point_for_x = point;
                object_point = &object_points_base[4];
                {
                    s32 row_offset = step << 2;

                    do {
                    s32 random_value;
                    s32 half_step;
                    s16 x_base;

                    object_point->y = (s16)((u16)transform[4].y +
                                            row_offset);
                    random_value = func_80069EF8() % step;
                    object_index--;
                    row_offset -= step;
                    x_base = point_for_x->x;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    half_step = step >> 1;
                    ASM_KEEP(half_step);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    object_point->x = (s16)(x_base +
                                            random_value - half_step);
                    object_point--;
                    } while (object_index > 0);
                }

                object_index = 3;
                height4 = height << 2;
                object_point2 = &object_points_base[3];
                {
                s32 lo = layer_off;
                for (; object_index >= 0; object_index--) {
                    s16 value;
                    s16 color_a;
                    s32 next_index;
                    void *entry;
                    register u32 primitive_color ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                    {
                        void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                        entry = ((S_80024C7C_2 *)context)->unk_8D0;
                        ((S_80024C7C_2 *)context)->unk_8D0 =
                            (void *)((u8 *)entry + 0x34);
                    }
                    primitive_color = 0x00808080;
                    ((S_80024C7C_3 *)entry)->unk_04 = primitive_color;
                    func_800666F4(entry, primitive_color);
                    func_80066640(entry, 1);
                    ((S_80024C7C_3 *)entry)->unk_16 =
                        func_80066460(0, 1, 0x2C0, 0x100);
                    ((S_80024C7C_3 *)entry)->unk_0E = func_8006649C(0xA0, 0x1F7);

                    value = object_point2->y;
                    ((S_80024C7C_3 *)entry)->unk_1A = (u16)value;
                    ((S_80024C7C_3 *)entry)->unk_0A = (u16)value;
                    next_index = object_index + 1;
                    next_point = &object_points_base[next_index];
                    value = next_point->y;
                    ((S_80024C7C_3 *)entry)->unk_22 = (u16)value;
                    ((S_80024C7C_3 *)entry)->unk_12 = (u16)value;

                    step = ((s32)((S_80024C7C_4 *)((u8 *)transform_base + lo))->unk_02 -
                                  (s32)transform[4].y) >> 4;
                    if (step == 0) {
                        step = 1;
                    }
                    ((S_80024C7C_3 *)entry)->unk_08 =
                        (u16)(object_point2->x - step);
                    ((S_80024C7C_3 *)entry)->unk_10 =
                        (u16)(next_point->x - step);
                    ((S_80024C7C_3 *)entry)->unk_18 =
                        (s16)(((S_80024C7C_3 *)entry)->unk_08 + step);
                    ((S_80024C7C_3 *)entry)->unk_20 =
                        (s16)(((S_80024C7C_3 *)entry)->unk_10 + step);

                    color_a = ((S_80024C7C_0 *)node)->unk_40;
                    ((S_80024C7C_3 *)entry)->unk_1C = (u8)color_a;
                    ((S_80024C7C_3 *)entry)->unk_0C = (u8)color_a;
                    color_a = (s16)(color_a + ((S_80024C7C_0 *)node)->unk_44);
                    ((S_80024C7C_3 *)entry)->unk_24 = (s8)color_a;
                    ((S_80024C7C_3 *)entry)->unk_14 = (s8)color_a;
                    color_a = ((S_80024C7C_0 *)node)->unk_42;
                    ((S_80024C7C_3 *)entry)->unk_15 = (u8)color_a;
                    ((S_80024C7C_3 *)entry)->unk_0D = (u8)color_a;
                    color_a = (s16)(color_a + ((S_80024C7C_0 *)node)->unk_46);
                    ((S_80024C7C_3 *)entry)->unk_25 = (s8)color_a;
                    ((S_80024C7C_3 *)entry)->unk_1D = (s8)color_a;

                    {
                        void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                        ((S_80024C7C_3 *)entry)->unk_00.s = (s32)(
                            (((S_80024C7C_3 *)entry)->unk_00.u & 0xFF000000) |
                            (((S_80024C7C_5 *)((u8 *)(height4 + (u32)context)))->unk_B0 &
                             color_mask));
                    }
                    object_point2--;
                    {
                        void *context = ((S_80024C7C_1 *)global_base)->unk_00;
                        ((S_80024C7C_5 *)((u8 *)(height4 + (u32)context)))->unk_B0 = (u32)(
                            (((S_80024C7C_5 *)((u8 *)(height4 + (u32)context)))->unk_B0 &
                             0xFF000000) |
                            ((u32)(u8 *)entry & color_mask));
                    }
                }
                }
            }
            point--;
            layer_off -= 4;
        }

        next_node = ((S_80024C7C_6_pre *)arg0)[-1].unk_00;
        if (next_node == NULL) {
            return 0;
        }
        arg0 = (u8 *)next_node + 0x20;
    }
}
