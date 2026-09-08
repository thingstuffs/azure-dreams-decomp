#include "common.h"

typedef struct DungeonDrawState {
    u8 pad[0x8D0];
    u8 *next_primitive;
} DungeonDrawState;

typedef struct DungeonShape {
    u8 pad00[0x34];
    s32 unk34;
    u8 unk38;
    u8 pad39;
    u8 unk3A;
    u8 pad3B;
    u8 unk3C;
    u8 pad3D;
    u8 unk3E;
    u8 pad3F;
    u16 unk40;
    u16 unk42;
    u8 pad44[2];
    s16 unk46;
} DungeonShape;

#ifdef __mips__
typedef union DungeonSignedProduct {
    signed long long value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} DungeonSignedProduct;
#endif

extern DungeonDrawState *D_80083160[];
extern s32 func_80065420(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80066640(void *arg0, s32 arg1);
extern void func_800666F4(void *arg0);

#define PRIM_U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PRIM_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PRIM_U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

/* Project linked shapes and queue four textured quads for each visible shape. */
s32 func_800249BC(void *shape_data)
{
    u16 points[5][2];
    s32 half_width;
    void *next_node;
    register DungeonShape *shape ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef __mips__
    u8 *draw_state_page = (u8 *)0x80080000;
    DungeonDrawState **draw_state_p = ({
        ASM_KEEP_NV(draw_state_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        (DungeonDrawState **)(draw_state_page + 0x3160);
    });
#else
    DungeonDrawState **draw_state_p = D_80083160;
#endif
    register u16 (*points_base)[2] ASM_REG("$22") = points;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 *half_width_p = &half_width;
    register u32 address_mask ASM_REG("$21") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 depth_or_tag_mask;
    s32 y_span;
    s32 width_divisor;
    register s32 point_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifdef __mips__
    DungeonSignedProduct depth_product;
    s32 depth_sign;
    register s32 scaled_depth ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#endif

next_shape:
    shape = (DungeonShape *)shape_data;
    depth_or_tag_mask = 0;
    point_index = 4;
    {
        u16 (*point)[2] = &points_base[4];
        s32 vertex_offset = 0x24;

        for (; point_index >= 0; point_index--) {
            s32 point_depth;
            s32 biased_depth_sum;

            point_depth = func_80065420((u8 *)shape + vertex_offset, point,
                                   half_width_p, half_width_p);
            biased_depth_sum = depth_or_tag_mask - 8;
            depth_or_tag_mask = biased_depth_sum + point_depth;
            point--;
            vertex_offset -= 8;
        }
    }

    y_span = (s16)points[0][1];
    y_span = y_span - (s16)points[4][1];
    width_divisor = shape->unk46;
    if (y_span < 0) {
        y_span = -y_span;
    }
    y_span = y_span / (width_divisor + 2);
#ifdef __mips__
    depth_product.value = (signed long long)depth_or_tag_mask * 0x66666667;
    depth_sign = depth_or_tag_mask >> 31;
    scaled_depth = depth_product.word.hi >> 1;
    depth_or_tag_mask = scaled_depth - depth_sign;
#else
    depth_or_tag_mask = depth_or_tag_mask / 5;
#endif
    half_width = y_span;

    if ((u32)depth_or_tag_mask < 0x1E0) {
        point_index = 0;
        {
            s32 ordering_offset = depth_or_tag_mask * 4;

            depth_or_tag_mask = 0xFF000000;

            do {
                DungeonDrawState *draw_state = *draw_state_p;
                u8 *primitive = draw_state->next_primitive;
                register s32 next_index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u16 *current_point ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u16 *next_point ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                u16 texture_attr;
                u16 start_x;
                u16 width_u16;
                u16 start_y;
                u16 end_y;
                register u8 tex_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                register u8 tex_span ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                u32 *ordering_entry;
                DungeonDrawState *ordering_state;
                register u32 primitive_tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                u32 ordering_tag;
                u32 saved_ordering_tag;

                draw_state->next_primitive = primitive + 0x28;
                PRIM_U32(primitive, 4) = shape->unk34;
                func_800666F4(primitive);
                func_80066640(primitive, 1);

                current_point = points_base[point_index];
                ASM_KEEP_NV(current_point);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                texture_attr = shape->unk40;
                ASM_KEEP_NV(texture_attr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                next_index = point_index + 1;
                ASM_KEEP_NV(next_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                PRIM_U16(primitive, 0x16) = texture_attr;
                texture_attr = shape->unk42;
                ASM_KEEP_NV(texture_attr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                next_point = (u16 *)(next_index * 4);
                PRIM_U16(primitive, 0x0E) = texture_attr;

                start_x = current_point[0];
                ASM_KEEP_NV(start_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                width_u16 = *(u16 *)(void *)&half_width;
                ASM_KEEP_NV(width_u16);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                next_point =
                    (u16 *)((u8 *)points_base + (u32)next_point);
                ASM_KEEP_NV(next_point);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                PRIM_U16(primitive, 0x08) = start_x - width_u16;
                PRIM_U16(primitive, 0x10) = next_point[0] - width_u16;
                PRIM_U16(primitive, 0x18) = current_point[0] + width_u16;
                PRIM_U16(primitive, 0x20) = next_point[0] + width_u16;

                start_y = current_point[1];
                PRIM_U16(primitive, 0x1A) = start_y;
                PRIM_U16(primitive, 0x0A) = start_y;
                end_y = next_point[1];
                PRIM_U16(primitive, 0x22) = end_y;
                PRIM_U16(primitive, 0x12) = end_y;

                tex_coord = shape->unk38;
                PRIM_U8(primitive, 0x1C) = tex_coord;
                PRIM_U8(primitive, 0x0C) = tex_coord;
                tex_span = shape->unk3C;
                tex_coord = tex_coord + tex_span;
                PRIM_U8(primitive, 0x24) = tex_coord;
                PRIM_U8(primitive, 0x14) = tex_coord;

                tex_coord = shape->unk3A;
                PRIM_U8(primitive, 0x25) = tex_coord;
                PRIM_U8(primitive, 0x1D) = tex_coord;
                tex_span = shape->unk3E;
                tex_coord = tex_coord + tex_span;
                PRIM_U8(primitive, 0x15) = tex_coord;
                PRIM_U8(primitive, 0x0D) = tex_coord;

                ordering_state = *draw_state_p;
                primitive_tag = PRIM_U32(primitive, 0);
                ordering_entry =
                    (u32 *)((u32)ordering_offset + (u32)ordering_state);
                ordering_tag = ordering_entry[0x2C];
                primitive_tag = (primitive_tag & depth_or_tag_mask) |
                                 (ordering_tag & address_mask);
                PRIM_U32(primitive, 0) = primitive_tag;
                ordering_state = *draw_state_p;
                ordering_entry =
                    (u32 *)((u32)ordering_offset + (u32)ordering_state);
                saved_ordering_tag = ordering_entry[0x2C];
                ordering_entry[0x2C] = (saved_ordering_tag & depth_or_tag_mask) |
                                       ((u32)primitive & address_mask);

                point_index = next_index;
            } while (point_index < 4);
        }
    }
    next_node = *(void **)((u8 *)shape_data - 8);
    if (next_node != 0) {
        shape_data = (u8 *)next_node + 0x20;
        goto next_shape;
    }
    return 0;
}
