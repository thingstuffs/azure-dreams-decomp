#include "common.h"
#include "shared/game_work.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v, s32 z);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void AddPrim(void *ot, void *prim);

/* Transform sprite parts into textured quads and add them to the ordering table. */
void func_80044D24(void *unused, u8 *sprite, s32 ot_depth)
{
    u8 **contexts;
    u8 *scratch;
    void *prim;
    u8 *context;
    u8 *parts;
    void *part;
    void *packet;
    s32 depth;
    s16 corner_x;
    s16 corner_y;
    u16 flags;
    u16 sprite_x;
    s32 origin_x;
    u8 uv_start;
    u8 uv_size;
    s32 page_or_flags;

    (void)unused;
    context = gameWork.unk_000;
    scratch = (u8 *)0x1F800000;
    depth = ot_depth;
    contexts = (u8 **)((void * *)(&gameWork));
    prim = *(void **)(context + 0x8D0);
    U32_AT(scratch, 0x20) = (u32)(context + 0x70);
    U32_AT(scratch, 0x38) = 0x1000;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();

    parts = *(u8 **)(sprite + 8);
    flags = U16_AT(sprite, 0x14) | 0x8000;
    U16_AT(sprite, 0x14) = flags;
    U16_AT(scratch, 0x24) = flags;
    part = parts + 1;
    U32_AT(scratch, 0x30) = U16_AT(sprite, 0x1C);
    origin_x = S16_AT(scratch, 0);
    packet = (u8 *)prim + 4;
    U32_AT(scratch, 0x34) = U16_AT(sprite, 0x1E);
    sprite_x = U16_AT(sprite, 0x20);
    U32_AT(scratch, 0x40) = origin_x + sprite_x;
    U32_AT(scratch, 0x44) = S16_AT(scratch, 2) + U16_AT(sprite, 0x22);
    TransMatrix(scratch + 0x50, scratch + 0x40, sprite_x);
    RotMatrix(sprite + 0x16, scratch + 0x50);
    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    SetRotMatrix(scratch + 0x50);
    SetTransMatrix(scratch + 0x50);

next_part:
    if (!(parts[0] & 0x20)) {
        s16 flipped_offset;
        uv_start = U8_AT(part, 7);
        U32_AT(scratch, 8) = uv_start;
        uv_size = U8_AT(part, 9);
        U32_AT(scratch, 0x10) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x10) = uv_size - 1;
        }

        uv_start = U8_AT(part, 8);
        U32_AT(scratch, 0xC) = uv_start;
        uv_size = U8_AT(part, 0xA);
        U32_AT(scratch, 0x14) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x14) = uv_size - 1;
        }

        if ((parts[0] ^ U16_AT(scratch, 0x24)) & 1) {
            if (U16_AT(sprite, 0x14) & 0x400) {
                flipped_offset = -(S8_AT(part, 1) << 1);
            } else {
                flipped_offset = -S8_AT(part, 1);
            }
            S16_AT(scratch, 0x80) = flipped_offset;
            S16_AT(scratch, 0x70) = flipped_offset;
            corner_x = flipped_offset - U16_AT(scratch, 0x10);
        } else {
            s16 offset = S8_AT(part, 1);
            if (U16_AT(sprite, 0x14) & 0x400) {
                offset <<= 1;
            }
            S16_AT(scratch, 0x80) = offset;
            S16_AT(scratch, 0x70) = offset;
            offset += U16_AT(scratch, 0x10);
            corner_x = offset;
        }
        S16_AT(scratch, 0x88) = corner_x;
        S16_AT(scratch, 0x78) = corner_x;

        if ((parts[0] ^ U16_AT(scratch, 0x24)) & 2) {
            if (U16_AT(sprite, 0x14) & 0x400) {
                flipped_offset = -(S8_AT(part, 2) << 1);
            } else {
                flipped_offset = -S8_AT(part, 2);
            }
            S16_AT(scratch, 0x7A) = flipped_offset;
            S16_AT(scratch, 0x72) = flipped_offset;
            corner_y = flipped_offset - U16_AT(scratch, 0x14);
        } else {
            s16 offset = S8_AT(part, 2);
            if (U16_AT(sprite, 0x14) & 0x400) {
                offset <<= 1;
            }
            S16_AT(scratch, 0x7A) = offset;
            S16_AT(scratch, 0x72) = offset;
            offset += U16_AT(scratch, 0x14);
            corner_y = offset;
        }
        S16_AT(scratch, 0x8A) = corner_y;
        S16_AT(scratch, 0x82) = corner_y;

        gte_ldv0(scratch + 0x70);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 8);

        gte_ldv0(scratch + 0x78);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x10);

        gte_ldv0(scratch + 0x80);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x18);

        gte_ldv0(scratch + 0x88);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x20);

        U8_AT(packet, -1) = 9;
        U16_AT(sprite, 0x14) &= 0x7FFF;
        U32_AT(scratch, 0x10) += U32_AT(scratch, 8);
        U32_AT(scratch, 0x14) += U32_AT(scratch, 0xC);
        U32_AT(scratch, 0x14) <<= 8;
        U32_AT(scratch, 0xC) <<= 8;

        if (U16_AT(scratch, 0x24) & 0x100) {
            U16_AT(packet, 0xA) = U16_AT(sprite, 0x12);
        } else {
            U16_AT(packet, 0xA) =
                U16_AT(sprite, 0x12) + U16_AT(part, 5);
        }
        S16_AT(packet, 8) = U16_AT(scratch, 0xC) + U16_AT(scratch, 8);
        S16_AT(packet, 0x10) =
            U16_AT(scratch, 0xC) + U16_AT(scratch, 0x10);

        {
            u16 tpage;
            page_or_flags = U16_AT(sprite, 0x10);
            if (page_or_flags != 0) {
                tpage = page_or_flags +
                    (U16_AT(part, 3) & 0xFF9F);
            } else {
                tpage = U16_AT(part, 3);
            }
            U16_AT(packet, 0x12) = tpage;
        }
        S16_AT(packet, 0x18) =
            U16_AT(scratch, 0x14) + U16_AT(scratch, 8);
        S16_AT(packet, 0x20) =
            U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

        if (S16_AT(scratch, 0x50) >= 0x1800) {
            u8 edge_u = U8_AT(packet, 0x20);
            U8_AT(packet, 0x20) = edge_u + 0xFF;
            U8_AT(packet, 0x10) = edge_u;
        }
        if (S16_AT(scratch, 0x58) >= 0x1800) {
            u8 edge_v = U8_AT(packet, 0x21);
            U8_AT(packet, 0x21) = edge_v + 0xFF;
            U8_AT(packet, 0x19) = edge_v;
        }
        if (S16_AT(packet, 4) > S16_AT(packet, 0x1C)) {
            u8 edge_u = U8_AT(packet, 0x20);
            U8_AT(packet, 0x20) = edge_u + 0xFF;
            U8_AT(packet, 0x10) = edge_u;
        }
        if (S16_AT(packet, 6) > S16_AT(packet, 0x1E)) {
            u8 edge_v = U8_AT(packet, 0x21);
            U8_AT(packet, 0x21) = edge_v + 0xFF;
            U8_AT(packet, 0x19) = edge_v;
        }

        {
            u8 prim_code;
            prim_code = U8_AT(part, 0);
            sprite[0xF] = prim_code;
            page_or_flags = U16_AT(scratch, 0x24);
            if (page_or_flags & 8) {
                u8 blend_code;
                if (page_or_flags & 4) {
                    blend_code = prim_code | 2;
                } else {
                    blend_code = prim_code & 0xFD;
                }
                sprite[0xF] = blend_code;
            }
        }

        {
            void *draw_prim;
            s32 ot_offset;
            draw_prim = prim;
            prim = (u8 *)prim + 0x28;
            ot_offset = (s16)depth * 4;
            {
                u32 color_code;
                color_code = U32_AT(sprite, 0xC);
                U32_AT(packet, 0) = color_code;
            }
            {
                u32 ot_base;
                ot_base = U32_AT(scratch, 0x20);
                packet = (u8 *)packet + 0x28;
                AddPrim((u8 *)ot_base + ot_offset, draw_prim);
            }
        }
    }

    part = (u8 *)part + 0xC;
    if ((s8)parts[0] >= 0) {
        parts += 0xC;
        goto next_part;
    }

    PopMatrix();
    *(void **)(contexts[0] + 0x8D0) = prim;
}
