#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct {
    s16 vx;
    s16 vy;
} DVEC;

extern s32 func_8004C010(void *a, void *b);
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);

/* Builds a triangle fan for an ellipse or quarter ellipse. */
void *func_8004B954(void *color_a, void *color_b, void *primitives,
                    void *color_data, void *style, s32 *out_count, s32 shaded)
{
    DVEC edge_pos;
    s32 center_x;
    s32 radius_x;
    s32 angle_step;
    s32 first_segment;
    s32 segment;
    register s32 angle ASM_REG("$18");   /* MATCH pin: slus-diff */
    s32 center_y;
    s32 segment_count;
    s32 radius_y;
    register u8 *template ASM_REG("$20");   /* MATCH pin: slus-diff */
    u8 *flat_tri;
    u8 *shaded_tri;
    register u8 *field_ptr ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u8 flags;
    u32 copied_word;

    first_segment = 1;
    template = (u8 *)primitives;
    flat_tri = template;
    radius_x = S16_AT(flat_tri, 0x10) - S16_AT(flat_tri, 0x08);
    radius_y = S16_AT(flat_tri, 0x22) - S16_AT(flat_tri, 0x0A);
    flags = U8_AT(style, 0);
    shaded_tri = template;
    if (!(flags & 0x20)) {
        segment_count = 0x10;
        if (flags & 0x10) {
            segment_count = 0x20;
        }
    } else {
        segment_count = 0x40;
    }
    angle_step = 0x1000 / segment_count;
    flags = U8_AT(style, 0);
    if (flags & 0x40) {
        if (flags & 1) {
            first_segment += 0x400;
            center_x = S16_AT(primitives, 0x08) - radius_x;
        } else {
            center_x = S16_AT(primitives, 0x08);
        }
        if (U8_AT(style, 0) & 2) {
            first_segment += 0x800;
            {
                s32 corner_y = S16_AT(primitives, 0x0A);
                center_y = corner_y - radius_y;
            }
        } else {
            center_y = S16_AT(primitives, 0x0A);
        }
        segment_count = segment_count / 4;
    } else {
        radius_y = radius_y >> 1;
        radius_x = radius_x >> 1;
        center_x = S16_AT(primitives, 0x08) + radius_x;
        {
            s32 corner_y = S16_AT(primitives, 0x0A);
            center_y = corner_y + radius_y;
        }
    }

    if (radius_x != 0 && radius_y != 0) {
        edge_pos.vx = ((rcos(0) * radius_x) >> 12) + center_x;
        {
            s32 offset_y = (rsin(0) * radius_y) >> 12;
            edge_pos.vy = offset_y + center_y;
        }
        S16_AT(shaded_tri, 0x08) = S8_AT(style, 0x08) + center_x;
        S16_AT(shaded_tri, 0x0A) = S8_AT(style, 0x09) + center_y;
        if (shaded == 0) {
            U8_AT(shaded_tri, 0x03) = 4;
        } else {
            U8_AT(shaded_tri, 0x03) = 6;
        }
        field_ptr = shaded_tri + 4;
        U32_AT(primitives, 0x04) = U32_AT(style, 0x04);
        func_8004C010(field_ptr, color_a);
        func_8004C010(field_ptr, color_b);
        U8_AT(shaded_tri, 0x07) = U8_AT(style, 0x01) & 0x7F;
        field_ptr = shaded_tri + 0xC;
        if (shaded != 0) {
            color_data = (void *)((u8 *)color_data + 0xC);
            U32_AT(shaded_tri, 0x0C) = U32_AT(color_data, 0);
            func_8004C010(field_ptr, color_a);
            func_8004C010(field_ptr, color_b);
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            U32_AT(shaded_tri, 0x14) = U32_AT(shaded_tri, 0x0C);
            field_ptr = shaded_tri + 0x18;
            segment = first_segment;
            if (segment <= first_segment + segment_count) {
                angle = segment * angle_step;
                do {
                    U32_AT(shaded_tri, 0x00) = U32_AT(template, 0x00);
                    U32_AT(field_ptr, -0x14) = U32_AT(template, 0x04);
                    U32_AT(field_ptr, -0x10) = U32_AT(template, 0x08);
                    U32_AT(field_ptr, -0x0C) = U32_AT(template, 0x0C);
                    copied_word = U32_AT(template, 0x14);
                    U32_AT(field_ptr, -0x08) = *(u32 *)&edge_pos;
                    U32_AT(field_ptr, -0x04) = copied_word;
                    edge_pos.vx = ((rcos(angle) * radius_x) >> 12) + center_x;
                    segment++;
                    shaded_tri += 0x1C;
                    {
                        s32 offset_y = (rsin(angle) * radius_y) >> 12;
                        edge_pos.vy = offset_y + center_y;
                    }
                    angle += angle_step;
                    U32_AT(field_ptr, 0x00) = *(u32 *)&edge_pos;
                    field_ptr += 0x1C;
                } while (segment <= first_segment + segment_count);
            }
        } else {
            segment = first_segment;
            field_ptr = flat_tri + 0x10;
            if (segment <= first_segment + segment_count) {
                angle = segment * angle_step;
                do {
                    U32_AT(flat_tri, 0x00) = U32_AT(template, 0x00);
                    U32_AT(field_ptr, -0x0C) = U32_AT(template, 0x04);
                    copied_word = U32_AT(template, 0x08);
                    U32_AT(field_ptr, -0x04) = *(u32 *)&edge_pos;
                    U32_AT(field_ptr, -0x08) = copied_word;
                    edge_pos.vx = ((rcos(angle) * radius_x) >> 12) + center_x;
                    segment++;
                    flat_tri += 0x14;
                    {
                        s32 offset_y = (rsin(angle) * radius_y) >> 12;
                        edge_pos.vy = offset_y + center_y;
                    }
                    angle += angle_step;
                    U32_AT(field_ptr, 0x00) = *(u32 *)&edge_pos;
                    field_ptr += 0x14;
                } while (segment <= first_segment + segment_count);
            }
        }
        *out_count = segment_count;
    } else {
        if (shaded != 0) {
            color_data = (void *)((u8 *)color_data + 0xC);
        }
        *out_count = 0;
    }
    return color_data;
}
