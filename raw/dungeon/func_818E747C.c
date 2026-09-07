#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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

        points[4].x = (s16)(FIELD(node, u16, 0x0C) + 0x20);
        points[4].y = (s16)(FIELD(node, u16, 0x0E) + 0x20);
        points[4].z = FIELD(node, s16, 0x10);
        for (layer = 3; layer >= 0; layer--) {
            points_base[layer].x = (s16)(FIELD(node, u16, 0x0C) +
                                    ((layer >> 1) << 6));
            points_base[layer].y = (s16)(FIELD(node, u16, 0x0E) +
                                    ((layer % 2) << 6));
            points_base[layer].z = (s16)(FIELD(node, u16, 0x10) +
                                    FIELD(node, u16, 0x4A));
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
                    ASM_SCHED_BARRIER();
                    half_step = step >> 1;
                    ASM_KEEP(half_step);
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
                    register u32 primitive_color ASM_REG("$5");

                    {
                        void *context = FIELD(global_base, void *, 0);
                        entry = FIELD(context, void *, 0x8D0);
                        FIELD(context, void *, 0x8D0) =
                            (void *)((u8 *)entry + 0x34);
                    }
                    primitive_color = 0x00808080;
                    FIELD(entry, u32, 4) = primitive_color;
                    func_800666F4(entry, primitive_color);
                    func_80066640(entry, 1);
                    FIELD(entry, s16, 0x16) =
                        func_80066460(0, 1, 0x2C0, 0x100);
                    FIELD(entry, s16, 0x0E) = func_8006649C(0xA0, 0x1F7);

                    value = object_point2->y;
                    FIELD(entry, u16, 0x1A) = (u16)value;
                    FIELD(entry, u16, 0x0A) = (u16)value;
                    next_index = object_index + 1;
                    next_point = &object_points_base[next_index];
                    value = next_point->y;
                    FIELD(entry, u16, 0x22) = (u16)value;
                    FIELD(entry, u16, 0x12) = (u16)value;

                    step = ((s32)FIELD((u8 *)transform_base + lo, s16, 2) -
                                  (s32)transform[4].y) >> 4;
                    if (step == 0) {
                        step = 1;
                    }
                    FIELD(entry, u16, 8) =
                        (u16)(object_point2->x - step);
                    FIELD(entry, u16, 0x10) =
                        (u16)(next_point->x - step);
                    FIELD(entry, s16, 0x18) =
                        (s16)(FIELD(entry, u16, 8) + step);
                    FIELD(entry, s16, 0x20) =
                        (s16)(FIELD(entry, u16, 0x10) + step);

                    color_a = FIELD(node, u8, 0x40);
                    FIELD(entry, u8, 0x1C) = (u8)color_a;
                    FIELD(entry, u8, 0x0C) = (u8)color_a;
                    color_a = (s16)(color_a + FIELD(node, u8, 0x44));
                    FIELD(entry, s8, 0x24) = (s8)color_a;
                    FIELD(entry, s8, 0x14) = (s8)color_a;
                    color_a = FIELD(node, u8, 0x42);
                    FIELD(entry, u8, 0x15) = (u8)color_a;
                    FIELD(entry, u8, 0x0D) = (u8)color_a;
                    color_a = (s16)(color_a + FIELD(node, u8, 0x46));
                    FIELD(entry, s8, 0x25) = (s8)color_a;
                    FIELD(entry, s8, 0x1D) = (s8)color_a;

                    {
                        void *context = FIELD(global_base, void *, 0);
                        FIELD(entry, s32, 0) = (s32)(
                            (FIELD(entry, u32, 0) & 0xFF000000) |
                            (FIELD((u8 *)(height4 + (u32)context), u32, 0xB0) &
                             color_mask));
                    }
                    object_point2--;
                    {
                        void *context = FIELD(global_base, void *, 0);
                        FIELD((u8 *)(height4 + (u32)context), u32, 0xB0) = (u32)(
                            (FIELD((u8 *)(height4 + (u32)context), u32, 0xB0) &
                             0xFF000000) |
                            ((u32)(u8 *)entry & color_mask));
                    }
                }
                }
            }
            point--;
            layer_off -= 4;
        }

        next_node = FIELD(arg0, void *, -8);
        if (next_node == NULL) {
            return 0;
        }
        arg0 = (u8 *)next_node + 0x20;
    }
}
