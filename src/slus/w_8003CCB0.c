#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v);
extern void RotMatrix(void *r, void *m);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void RotTransSV(void *in, void *out, void *flag);
extern void DrawPrim(void *p);
extern s32 rsin(s32);
extern void *func_8004E298(void *a0, void *a1, s32 a2);

extern s16 D_80080AAC;
extern void *D_80080AB0;
extern s16 D_80080AA4;
extern u16 D_80080AA8;
extern u8 D_8006CDB8[14];
extern u8 D_80083798[];
extern s16 D_80083858[64];
extern s16 D_800838D8[64];
extern void *D_80083160[3];

typedef union { struct { u8 u, v; } c; u16 word; } UVPair;
typedef struct {
    union { u32 word; u8 bytes[4]; } tag;
    u8 r, g, b, code;
    s16 x0, y0;
    UVPair uv0;
    u16 clut;
    s16 x1, y1;
    UVPair uv1;
    u16 tpage;
    s16 x2, y2;
    UVPair uv2;
    u16 pad2;
    s16 x3, y3;
    UVPair uv3;
    u16 pad3;
} SpriteQuad;

/* Draw fourteen sprites with interpolated positions and pulsing color. */
void func_8003CCB0(s32 blend_step)
{
    u8 *scratch;
    SpriteQuad *packet;
    u8 *sprite_uv;
    u8 *quad;
    u8 *transform_flags;
    u8 *sprite_base;
    s32 sprite_index;
    u8 sprite_key[2];
    u8 **render_state;
    s32 uv_start;
    s32 uv_size;
    s32 width;
    s32 height;
    s32 path_offset;
    s32 shade;
    s32 colour;

    scratch = (u8 *)0x1F800000;
    render_state = (u8 **)D_80083160;

    if (D_80080AAC == 0) {
        u8 *sprite_slot;
        s32 origin_offset;
        u8 *sprite_ids;
        sprite_index = 0;
        sprite_ids = D_8006CDB8;
        origin_offset = -4;
        sprite_slot = D_80083798;
        D_80080AAC = D_80080AAC + 1;
        sprite_key[1] = 0;
        do {
            sprite_key[0] = *(u8 *)(sprite_index + (u32)sprite_ids);
            colour = (s32)((u8 *)func_8004E298(sprite_slot, sprite_key, 0));
            S8_AT((u8 *)colour, 3) = origin_offset;
            S8_AT((u8 *)colour, 2) = origin_offset;
            if (sprite_index == 0) {
                D_80080AB0 = (u8 *)colour;
            }
            sprite_index++;
            sprite_slot += 0xC;
        } while (sprite_index < 0xE);
    }

    quad = *(u8 **)(render_state[0] + 0x8D0);
    sprite_index = 0;
    transform_flags = scratch + 0x94;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();
    {
        colour = (s32)((u8 *)D_80080AB0);
        sprite_base = ((u8 *)colour) + 4;
    }
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    packet = (SpriteQuad *)quad;

    do {
        sprite_uv = sprite_base + sprite_index * 12;
        path_offset = sprite_index << 2;
        {
            s32 start_x = *(s16 *)((u8 *)D_80083858 + path_offset);
            s32 end_x = *(s16 *)((u8 *)D_80083858 + 4 + path_offset);
            U32_AT(scratch, 0x40) = start_x + ((end_x - start_x) * blend_step) / 8;
        }
        {
            s32 start_y = *(s16 *)((u8 *)D_800838D8 + path_offset);
            s32 end_y = *(s16 *)((u8 *)D_800838D8 + 4 + path_offset);
            U32_AT(scratch, 0x44) = start_y + ((end_y - start_y) * blend_step) / 8;
        }
        TransMatrix(scratch + 0x50, scratch + 0x40);
        RotMatrix(scratch + 0x28, scratch + 0x50);
        SetRotMatrix(scratch + 0x50);
        SetTransMatrix(scratch + 0x50);

        uv_start = U8_AT(sprite_uv, 4);
        U32_AT(scratch, 0x08) = uv_start;
        uv_size = U8_AT(sprite_uv, 6);
        U32_AT(scratch, 0x10) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x10) = uv_size - 1;
        }
        uv_start = U8_AT(sprite_uv, 5);
        U32_AT(scratch, 0x0C) = uv_start;
        uv_size = U8_AT(sprite_uv, 7);
        U32_AT(scratch, 0x14) = uv_size;
        if (uv_start + uv_size >= 0x100) {
            U32_AT(scratch, 0x14) = uv_size - 1;
        }

        {
            s16 edge_x = S8_AT(sprite_uv, -2);
            width = ((u16 *)scratch)[8];
            S16_AT(scratch, 0x80) = edge_x;
            S16_AT(scratch, 0x70) = edge_x;
            edge_x = edge_x + width;
            S16_AT(scratch, 0x88) = edge_x;
            S16_AT(scratch, 0x78) = edge_x;
        }
        {
            s16 edge_y = S8_AT(sprite_uv, -1);
            height = ((u16 *)scratch)[10];
            S16_AT(scratch, 0x7A) = edge_y;
            S16_AT(scratch, 0x72) = edge_y;
            edge_y = edge_y + height;
            S16_AT(scratch, 0x8A) = edge_y;
            S16_AT(scratch, 0x82) = edge_y;
        }

        RotTransSV(scratch + 0x70, quad + 0x08, transform_flags);
        RotTransSV(scratch + 0x78, quad + 0x10, transform_flags);
        RotTransSV(scratch + 0x80, quad + 0x18, transform_flags);
        RotTransSV(scratch + 0x88, quad + 0x20, transform_flags);

        {
            U32_AT(scratch, 0x10) += U32_AT(scratch, 0x08);
            U32_AT(scratch, 0x14) += U32_AT(scratch, 0x0C);
            U32_AT(scratch, 0x14) <<= 8;
            U32_AT(scratch, 0x0C) <<= 8;
        }

        packet->clut = U16_AT(sprite_uv, 2);
        packet->uv0.word = ((u16 *)scratch)[6] + ((u16 *)scratch)[4];
        packet->uv1.word = ((u16 *)scratch)[6] + ((u16 *)scratch)[8];
        packet->tpage = U16_AT(sprite_uv, 0);
        packet->uv2.word = ((u16 *)scratch)[10] + ((u16 *)scratch)[4];
        packet->uv3.word = ((u16 *)scratch)[10] + ((u16 *)scratch)[8];

        if (packet->x0 > packet->x3) {
            u8 right_u = packet->uv3.c.u;
            packet->uv3.c.u = right_u + 0xFF;
            packet->uv1.c.u = right_u;
        }
        if (packet->y0 > packet->y3) {
            u8 bottom_v = packet->uv3.c.v;
            packet->uv3.c.v = bottom_v + 0xFF;
            packet->uv2.c.v = bottom_v;
        }
        packet->tag.bytes[3] = 9;
        packet->code = 0x2C;

        {
            s32 pulse = (rsin((D_80080AA4 << 8) + (sprite_index << 6)) >> 6) + 0x80;
            s32 fade_shift = blend_step / 2;
            shade = pulse >> fade_shift;
        }
        packet->r = shade;
        colour = 0;
        if (D_80080AA8 == 0) {
            colour = shade;
        }
        {
            u8 *draw_quad = quad;
            quad += 0x28;
            packet->b = colour;
            packet->g = colour;
            packet->code |= 2;
            DrawPrim(draw_quad);
        }
        packet++;
        sprite_index++;
    } while (sprite_index < 0xE);

    PopMatrix();
    {
        *(u8 **)(render_state[0] + 0x8D0) = quad;
    }
}
