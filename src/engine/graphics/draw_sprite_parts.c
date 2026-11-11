#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "shared/gpu_packets.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v, s32 z);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);

/* Transform sprite parts into textured quads and add them to the ordering table. */
void draw_sprite_parts(void *unused, SpriteFrameState *sprite, s32 ot_depth)
{
    u8 **contexts;
    SpriteQuadScratch *scratch;
    void *prim;
    GpuContext *context;
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
    context = g_game_work.draw_buffer;
    scratch = (SpriteQuadScratch *)0x1F800000;
    depth = ot_depth;
    contexts = (u8 **)((void * *)(&g_game_work));
    prim = context->packetCursor;
    scratch->ordering_table = &context->orderTag070;
    scratch->input_z = 0x1000;
    scratch->translation_z = 0;
    scratch->vertices[3].z = 0;
    scratch->vertices[2].z = 0;
    scratch->vertices[1].z = 0;
    scratch->vertices[0].z = 0;
    PushMatrix();

    parts = sprite->source;
    flags = sprite->flags | 0x8000;
    sprite->flags = flags;
    scratch->sprite_flags = flags;
    part = parts + 1;
    scratch->input_x = sprite->scale_x;
    origin_x = (s16)scratch->position_x;
    packet = (u8 *)prim + 4;
    scratch->input_y = sprite->scale_y;
    sprite_x = sprite->offset_x;
    scratch->translation_x = origin_x + sprite_x;
    scratch->translation_y = (s16)scratch->position_y + sprite->offset_y;
    TransMatrix(&scratch->matrix, &scratch->translation_x, sprite_x);
    RotMatrix(&sprite->angle_x, &scratch->matrix);
    ScaleMatrix(&scratch->matrix, &scratch->input_x);
    SetRotMatrix(&scratch->matrix);
    SetTransMatrix(&scratch->matrix);

next_part:
    if (!(parts[0] & 0x20)) {
        s16 flipped_offset;
        uv_start = U8_AT(part, 7);
        scratch->uv_u_start = uv_start;
        uv_size = U8_AT(part, 9);
        scratch->uv_u_extent = uv_size;
        if (uv_start + uv_size >= 0x100) {
            scratch->uv_u_extent = uv_size - 1;
        }

        uv_start = U8_AT(part, 8);
        scratch->uv_v_start = uv_start;
        uv_size = U8_AT(part, 0xA);
        scratch->uv_v_extent = uv_size;
        if (uv_start + uv_size >= 0x100) {
            scratch->uv_v_extent = uv_size - 1;
        }

        if ((parts[0] ^ scratch->sprite_flags) & 1) {
            if (sprite->flags & 0x400) {
                flipped_offset = -(S8_AT(part, 1) << 1);
            } else {
                flipped_offset = -S8_AT(part, 1);
            }
            scratch->vertices[2].x = flipped_offset;
            scratch->vertices[0].x = flipped_offset;
            corner_x = flipped_offset - (u16)scratch->uv_u_extent;
        } else {
            s16 offset = S8_AT(part, 1);
            if (sprite->flags & 0x400) {
                offset <<= 1;
            }
            scratch->vertices[2].x = offset;
            scratch->vertices[0].x = offset;
            offset += (u16)scratch->uv_u_extent;
            corner_x = offset;
        }
        scratch->vertices[3].x = corner_x;
        scratch->vertices[1].x = corner_x;

        if ((parts[0] ^ scratch->sprite_flags) & 2) {
            if (sprite->flags & 0x400) {
                flipped_offset = -(S8_AT(part, 2) << 1);
            } else {
                flipped_offset = -S8_AT(part, 2);
            }
            scratch->vertices[1].y = flipped_offset;
            scratch->vertices[0].y = flipped_offset;
            corner_y = flipped_offset - (u16)scratch->uv_v_extent;
        } else {
            s16 offset = S8_AT(part, 2);
            if (sprite->flags & 0x400) {
                offset <<= 1;
            }
            scratch->vertices[1].y = offset;
            scratch->vertices[0].y = offset;
            offset += (u16)scratch->uv_v_extent;
            corner_y = offset;
        }
        scratch->vertices[3].y = corner_y;
        scratch->vertices[2].y = corner_y;

        gte_ldv0(&scratch->vertices[0]);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 8);

        gte_ldv0(&scratch->vertices[1]);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x10);

        gte_ldv0(&scratch->vertices[2]);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x18);

        gte_ldv0(&scratch->vertices[3]);
        gte_rtv0tr();
        gte_stsv((u8 *)prim + 0x20);

        U8_AT(packet, -1) = 9;
        sprite->flags &= 0x7FFF;
        scratch->uv_u_extent += scratch->uv_u_start;
        scratch->uv_v_extent += scratch->uv_v_start;
        scratch->uv_v_extent <<= 8;
        scratch->uv_v_start <<= 8;

        if (scratch->sprite_flags & 0x100) {
            U16_AT(packet, 0xA) = sprite->clut;
        } else {
            U16_AT(packet, 0xA) =
                sprite->clut + U16_AT(part, 5);
        }
        S16_AT(packet, 8) = (u16)scratch->uv_v_start + (u16)scratch->uv_u_start;
        S16_AT(packet, 0x10) =
            (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;

        {
            u16 tpage;
            page_or_flags = sprite->tpage_abr;
            if (page_or_flags != 0) {
                tpage = page_or_flags +
                    (U16_AT(part, 3) & 0xFF9F);
            } else {
                tpage = U16_AT(part, 3);
            }
            U16_AT(packet, 0x12) = tpage;
        }
        S16_AT(packet, 0x18) =
            (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
        S16_AT(packet, 0x20) =
            (u16)scratch->uv_v_extent + (u16)scratch->uv_u_extent;

        if (scratch->matrix.m[0][0] >= 0x1800) {
            u8 edge_u = U8_AT(packet, 0x20);
            U8_AT(packet, 0x20) = edge_u + 0xFF;
            U8_AT(packet, 0x10) = edge_u;
        }
        if (scratch->matrix.m[1][1] >= 0x1800) {
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
            sprite->color.c.code = prim_code;
            page_or_flags = scratch->sprite_flags;
            if (page_or_flags & 8) {
                u8 blend_code;
                if (page_or_flags & 4) {
                    blend_code = prim_code | 2;
                } else {
                    blend_code = prim_code & 0xFD;
                }
                sprite->color.c.code = blend_code;
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
                color_code = sprite->color.unsigned_word;
                U32_AT(packet, 0) = color_code;
            }
            {
                u32 *ot_base;
                ot_base = scratch->ordering_table;
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
