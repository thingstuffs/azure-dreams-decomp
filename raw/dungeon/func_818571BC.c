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

s32 func_800249BC(void *arg0)
{
    u16 points[5][2];
    s32 spread;
    void *next;
    register DungeonShape *shape ASM_REG("$20");
#ifdef __mips__
    register u8 *draw_state_page ASM_REG("$2") = (u8 *)0x80080000;
    register DungeonDrawState **draw_state_p ASM_REG("$23") = ({
        ASM_KEEP_NV(draw_state_page);
        (DungeonDrawState **)(draw_state_page + 0x3160);
    });
#else
    register DungeonDrawState **draw_state_p ASM_REG("$23") = D_80083160;
#endif
    register u16 (*points_base)[2] ASM_REG("$22") = points;
    s32 *spread_p = &spread;
    register u32 low_mask ASM_REG("$21") = 0x00FFFFFF;
    register s32 total ASM_REG("$18");
    register s32 distance ASM_REG("$3");
    s32 divisor;
    register s32 i ASM_REG("$19");
#ifdef __mips__
    DungeonSignedProduct product;
    register s32 sign ASM_REG("$2");
    register s32 high_shift ASM_REG("$4");
#endif

loop:
    ASM_KEEP(draw_state_p);
    ASM_KEEP(points_base);
    ASM_KEEP(spread_p);
    ASM_KEEP(low_mask);
        shape = (DungeonShape *)arg0;
        total = 0;
        ASM_KEEP(shape);
        ASM_KEEP(total);
        ASM_KEEP(i);
        i = 4;
        {
            register u16 (*point)[2] ASM_REG("$17") = &points_base[4];
            register s32 offset ASM_REG("$16") = 0x24;

            ASM_KEEP(point);
            ASM_KEEP(offset);
            for (; i >= 0; i--) {
                s32 result;
                register s32 adjusted_total ASM_REG("$3");

                result = func_80065420((u8 *)shape + offset, point,
                                       spread_p, spread_p);
                adjusted_total = total - 8;
                total = adjusted_total + result;
                point--;
                offset -= 8;
            }
        }

        distance = (s16)points[0][1];
        distance = distance - (s16)points[4][1];
        divisor = shape->unk46;
        if (distance < 0) {
            distance = -distance;
        }
        distance = distance / (divisor + 2);
#ifdef __mips__
        product.value = (signed long long)total * 0x66666667;
        sign = total >> 31;
        high_shift = product.word.hi >> 1;
        total = high_shift - sign;
#else
        total = total / 5;
#endif
        ASM_KEEP_NV(total);
        spread = distance;

        if ((u32)total < 0x1E0) {
            i = 0;
            {
                register s32 ordering_offset ASM_REG("$17") = total * 4;

                total = 0xFF000000;
                ASM_KEEP(ordering_offset);

                do {
                DungeonDrawState *draw_state = *draw_state_p;
                register u8 *primitive ASM_REG("$16") = draw_state->next_primitive;
                register s32 next_index ASM_REG("$6");
                register u16 *current_point ASM_REG("$4");
                register u16 *next_point ASM_REG("$3");
                register u16 shape_coord ASM_REG("$2");
                register u16 x0 ASM_REG("$2");
                register u16 spread_u ASM_REG("$5");
                u16 y0;
                u16 y1;
                register u8 c0 ASM_REG("$2");
                register u8 color_delta ASM_REG("$3");
                u32 *ordering_entry;
                register DungeonDrawState *ordering_state ASM_REG("$3");
                register u32 primitive_word ASM_REG("$2");
                register u32 ordering_word ASM_REG("$3");
                register u32 next_ordering_word ASM_REG("$2");

                draw_state->next_primitive = primitive + 0x28;
                PRIM_U32(primitive, 4) = shape->unk34;
                func_800666F4(primitive);
                func_80066640(primitive, 1);

                ASM_KEEP(primitive);
                current_point = points_base[i];
                ASM_KEEP_NV(current_point);
                shape_coord = shape->unk40;
                ASM_KEEP_NV(shape_coord);
                next_index = i + 1;
                ASM_KEEP_NV(next_index);
                PRIM_U16(primitive, 0x16) = shape_coord;
                shape_coord = shape->unk42;
                ASM_KEEP_NV(shape_coord);
                next_point = (u16 *)(next_index * 4);
                ASM_KEEP_NV(next_point);
                PRIM_U16(primitive, 0x0E) = shape_coord;

                x0 = current_point[0];
                ASM_KEEP_NV(x0);
                spread_u = *(u16 *)(void *)&spread;
                ASM_KEEP_NV(spread_u);
                next_point =
                    (u16 *)((u8 *)points_base + (u32)next_point);
                ASM_KEEP_NV(next_point);
                PRIM_U16(primitive, 0x08) = x0 - spread_u;
                PRIM_U16(primitive, 0x10) = next_point[0] - spread_u;
                PRIM_U16(primitive, 0x18) = current_point[0] + spread_u;
                PRIM_U16(primitive, 0x20) = next_point[0] + spread_u;

                y0 = current_point[1];
                PRIM_U16(primitive, 0x1A) = y0;
                PRIM_U16(primitive, 0x0A) = y0;
                y1 = next_point[1];
                PRIM_U16(primitive, 0x22) = y1;
                PRIM_U16(primitive, 0x12) = y1;

                c0 = shape->unk38;
                PRIM_U8(primitive, 0x1C) = c0;
                PRIM_U8(primitive, 0x0C) = c0;
                color_delta = shape->unk3C;
                ASM_KEEP_NV(color_delta);
                c0 = c0 + color_delta;
                PRIM_U8(primitive, 0x24) = c0;
                PRIM_U8(primitive, 0x14) = c0;

                c0 = shape->unk3A;
                PRIM_U8(primitive, 0x25) = c0;
                PRIM_U8(primitive, 0x1D) = c0;
                color_delta = shape->unk3E;
                ASM_KEEP_NV(color_delta);
                c0 = c0 + color_delta;
                PRIM_U8(primitive, 0x15) = c0;
                PRIM_U8(primitive, 0x0D) = c0;

                ordering_state = *draw_state_p;
                ASM_KEEP_NV(ordering_state);
                primitive_word = PRIM_U32(primitive, 0);
                ASM_KEEP_NV(primitive_word);
                ordering_entry =
                    (u32 *)((u32)ordering_offset + (u32)ordering_state);
                ordering_word = ordering_entry[0x2C];
                ASM_KEEP_NV(ordering_word);
                primitive_word = (primitive_word & total) |
                                 (ordering_word & low_mask);
                PRIM_U32(primitive, 0) = primitive_word;
                ordering_state = *draw_state_p;
                ordering_entry =
                    (u32 *)((u32)ordering_offset + (u32)ordering_state);
                next_ordering_word = ordering_entry[0x2C];
                ordering_entry[0x2C] = (next_ordering_word & total) |
                                       ((u32)primitive & low_mask);

                i = next_index;
                } while (i < 4);
            }
        }
        next = *(void **)((u8 *)arg0 - 8);
        if (next != 0) {
            arg0 = (u8 *)next + 0x20;
            goto loop;
        }
    return 0;
}

/* MECHANISM: The 0x58 frame holds points at sp+0x10 and spread at sp+0x28;
   s6/fp retain those bases while s7/s5 retain draw state and the low mask.
   Polygon dependencies now match retail; the traversal latch mirrors the matched
   local-loop analogue so the non-null edge encloses the next argument-home update. */
