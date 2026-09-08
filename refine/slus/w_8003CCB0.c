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

/* Draw fourteen sprites with interpolated positions and pulsing color. */
void func_8003CCB0(s32 blend_step)
{
    u8 *scratch;
    register u8 *packet ASM_REG("$17");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register u8 *sprite_uv ASM_REG("$19");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u8 *quad;
    u8 *transform_flags;
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
    register u8 *vertex_in ASM_REG("$4");   /* MATCH pin: slus-diff */
    register u8 *vertex_out ASM_REG("$5");   /* MATCH pin: slus-diff */
    register u8 *flags_out ASM_REG("$6");   /* MATCH pin: slus-diff */

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
            register u8 *sprite ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            sprite_key[0] = *(u8 *)(sprite_index + (u32)sprite_ids);
            sprite = (u8 *)func_8004E298(sprite_slot, sprite_key, 0);
            S8_AT(sprite, 3) = origin_offset;
            S8_AT(sprite, 2) = origin_offset;
            if (sprite_index == 0) {
                D_80080AB0 = sprite;
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
        register u8 *first_sprite ASM_REG("$3") = (u8 *)D_80080AB0;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        sprite_uv = first_sprite + 4;
    }
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    packet = quad + 7;

    do {
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

        vertex_in = scratch + 0x70;
        vertex_out = quad + 0x08;
        flags_out = transform_flags;
        {
            s32 origin_x = U8_AT(sprite_uv, -2);
            s32 edge_x;
            width = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(origin_x, width);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            edge_x = (origin_x << 24) >> 24;
            S16_AT(scratch, 0x80) = edge_x;
            S16_AT(scratch, 0x70) = edge_x;
            edge_x = edge_x + width;
            S16_AT(scratch, 0x88) = edge_x;
            S16_AT(scratch, 0x78) = edge_x;
        }
        {
            s32 origin_y = U8_AT(sprite_uv, -1);
            s32 edge_y;
            height = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(origin_y, height);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            edge_y = (origin_y << 24) >> 24;
            S16_AT(scratch, 0x7A) = edge_y;
            S16_AT(scratch, 0x72) = edge_y;
            edge_y = edge_y + height;
            S16_AT(scratch, 0x8A) = edge_y;
            S16_AT(scratch, 0x82) = edge_y;
        }

        RotTransSV(vertex_in, vertex_out, flags_out);
        RotTransSV(scratch + 0x78, quad + 0x10, transform_flags);
        RotTransSV(scratch + 0x80, quad + 0x18, transform_flags);
        RotTransSV(scratch + 0x88, quad + 0x20, transform_flags);

        {
            s32 uv_coord = U32_AT(scratch, 0x10);
            register s32 uv_start_u ASM_REG("$4") = U32_AT(scratch, 0x08);   /* MATCH pin: slus-diff */
            register s32 uv_end_v ASM_REG("$3") = U32_AT(scratch, 0x14);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            register s32 uv_start_v ASM_REG("$5") = U32_AT(scratch, 0x0C);   /* MATCH pin: slus-diff */
            uv_coord += uv_start_u;
            uv_end_v += uv_start_v;
            U32_AT(scratch, 0x10) = uv_coord;
            uv_coord = uv_start_v;
            ASM_KEEP_NV(uv_coord);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            U32_AT(scratch, 0x14) = uv_end_v << 8;
            U32_AT(scratch, 0x0C) = uv_coord << 8;
        }

        U16_AT(packet, 0x07) = U16_AT(sprite_uv, 2);
        S16_AT(packet, 0x05) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x0D) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x10);
        U16_AT(packet, 0x0F) = U16_AT(sprite_uv, 0);
        S16_AT(packet, 0x15) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x1D) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

        if (S16_AT(packet, 0x01) > S16_AT(packet, 0x19)) {
            u8 right_u = U8_AT(packet, 0x1D);
            U8_AT(packet, 0x1D) = right_u + 0xFF;
            U8_AT(packet, 0x0D) = right_u;
        }
        if (S16_AT(packet, 0x03) > S16_AT(packet, 0x1B)) {
            u8 bottom_v = U8_AT(packet, 0x1E);
            U8_AT(packet, 0x1E) = bottom_v + 0xFF;
            U8_AT(packet, 0x16) = bottom_v;
        }
        U8_AT(packet, -4) = 9;
        U8_AT(packet, 0) = 0x2C;

        {
            s32 pulse = (rsin((D_80080AA4 << 8) + (sprite_index << 6)) >> 6) + 0x80;
            s32 fade_shift = blend_step / 2;
            shade = pulse >> fade_shift;
        }
        U8_AT(packet, -3) = shade;
        colour = 0;
        if (D_80080AA8 == 0) {
            colour = shade;
        }
        {
            u8 *draw_quad = quad;
            quad += 0x28;
            sprite_uv += 0xC;
            sprite_index++;
            U8_AT(packet, -1) = colour;
            U8_AT(packet, -2) = colour;
            U8_AT(packet, 0) |= 2;
            DrawPrim(draw_quad);
        }
        packet += 0x28;
    } while (sprite_index < 0xE);

    PopMatrix();
    {
        *(u8 **)(render_state[0] + 0x8D0) = quad;
    }
}
