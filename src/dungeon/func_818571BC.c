#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_ovl_1876800.h"
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


extern DungeonDrawState *D_80083160[];
extern s32 func_80065420(void *world_vertex, void *screen_point, void *arg2, void *arg3);
extern void func_80066640(void *primitive, s32 arg1);
extern void func_800666F4(void *primitive);

typedef struct DungeonTag {
    unsigned addr : 24;
    unsigned len : 8;
} DungeonTag;

#define PRIM_U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PRIM_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PRIM_U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

#ifdef __mips__
typedef union DungeonSignedProduct {
    signed long long value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} DungeonSignedProduct;
#endif

/* Project linked shapes and queue four textured quads for each visible shape. */
s32 func_800249BC(void *shape_data)
{
    u16 points[5][2];
    s32 half_width;
    DungeonShape *shape;
    DungeonDrawState **draw_state_p = D_80083160;
    s32 depth_or_tag_mask;
    s32 y_span;
    s32 width_divisor;
    s32 point_index;
    s32 scaled_depth;
#ifdef __mips__
    DungeonSignedProduct depth_product;
    s32 depth_sign;
#endif

    do {
        shape = (DungeonShape *)shape_data;
        depth_or_tag_mask = 0;
        point_index = 4;
        for (; point_index >= 0; point_index--) {
            s32 point_depth;
            s32 biased_depth_sum;

            point_depth = func_80065420((u8 *)shape + 4 + point_index * 8, points[point_index],
                                   &half_width, &half_width);
            biased_depth_sum = depth_or_tag_mask - 8;
            depth_or_tag_mask = biased_depth_sum + point_depth;
        }

        y_span = (s16)points[0][1];
        y_span = y_span - (s16)points[4][1];
        width_divisor = shape->unk46;
        y_span = abs(y_span);
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

                do {
                    DungeonDrawState *draw_state = *draw_state_p;
                    u8 *primitive = draw_state->next_primitive;
                    s32 next_index;
                    u16 *current_point;
                    register u16 *next_point;
                    u16 texture_attr;
                    u16 start_x;
                    u16 width_u16;
                    u16 start_y;
                    u16 end_y;
                    u8 tex_coord;
                    u8 tex_coord2;
                    u8 tex_coord3;
                    u8 tex_span;

                    draw_state->next_primitive = primitive + 0x28;
                    PRIM_U32(primitive, 4) = shape->unk34;
                    func_800666F4(primitive);
                    func_80066640(primitive, 1);

                    current_point = points[point_index];
                    texture_attr = shape->unk40;
                    next_index = point_index + 1;
                    PRIM_U16(primitive, 0x16) = texture_attr;
                    texture_attr = shape->unk42;
                    PRIM_U16(primitive, 0x0E) = texture_attr;

                    start_x = current_point[0];
                    width_u16 = *(u16 *)(void *)&half_width;
                    next_point = points[next_index];
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
                    tex_coord2 = tex_coord + tex_span;
                    PRIM_U8(primitive, 0x24) = tex_coord2;
                    PRIM_U8(primitive, 0x14) = tex_coord2;

                    tex_coord2 = shape->unk3A;
                    PRIM_U8(primitive, 0x25) = tex_coord2;
                    PRIM_U8(primitive, 0x1D) = tex_coord2;
                    tex_span = shape->unk3E;
                    tex_coord3 = tex_coord2 + tex_span;
                    PRIM_U8(primitive, 0x15) = tex_coord3;
                    PRIM_U8(primitive, 0x0D) = tex_coord3;

                    ((DungeonTag *)primitive)->addr =
                        ((DungeonTag *)((u8 *)ordering_offset + (u32)*draw_state_p + 0xB0))->addr;
                    ((DungeonTag *)((u8 *)ordering_offset + (u32)*draw_state_p + 0xB0))->addr = (u32)primitive;

                    point_index = next_index;
                } while (point_index < 4);
            }
        }
        scaled_depth = *(s32 *)((u8 *)shape_data - 8);
        if (scaled_depth == 0) {
            break;
        }
        shape_data = (u8 *)scaled_depth + 0x20;
    } while (1);
    return 0;
}
