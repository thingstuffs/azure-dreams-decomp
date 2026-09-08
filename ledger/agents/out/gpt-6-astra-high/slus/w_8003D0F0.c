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
extern u8 D_800777AC[];
extern void *D_80083160[3];

/* Draw the sprite list as textured quads with optional horizontal and vertical flips. */
void func_8003D0F0(void)
{
    u8 *scratch;
    register u8 *packet ASM_REG("$17");   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
    register u8 *sprite_data ASM_REG("$18");   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
    u8 *prim;
    u8 *sprite;
    u8 *transform_flag;
    u8 **contexts;
    u8 *context;
    s32 tex_start;
    s32 tex_size;
    s32 x_end;
    s32 y_end;
    s32 width;
    s32 height;

    transform_flag = (u8 *)0x1F800094;
    context = (u8 *)D_80083160[0];
    scratch = (u8 *)0x1F800000;
    prim = *(u8 **)(context + 0x8D0);
    contexts = (u8 **)D_80083160;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();

    sprite = D_800777AC;
    U32_AT(scratch, 0x40) = 0x100;
    U32_AT(scratch, 0x44) = 0xB0;
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    TransMatrix((void *)0x1F800050, (void *)0x1F800040);
    RotMatrix((void *)0x1F800028, (void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);
    SetTransMatrix((void *)0x1F800050);
    sprite_data = sprite + 4;
    packet = prim + 4;

    do {
        tex_start = U8_AT(sprite_data, 4);
        U32_AT(scratch, 0x08) = tex_start;
        tex_size = U8_AT(sprite_data, 6);
        U32_AT(scratch, 0x10) = tex_size;
        if (tex_start + tex_size >= 0x100) {
            U32_AT(scratch, 0x10) = tex_size - 1;
        }

        tex_start = U8_AT(sprite_data, 5);
        U32_AT(scratch, 0x0C) = tex_start;
        tex_size = U8_AT(sprite_data, 7);
        U32_AT(scratch, 0x14) = tex_size;
        if (tex_start + tex_size >= 0x100) {
            U32_AT(scratch, 0x14) = tex_size - 1;
        }

        if (sprite[0] & 1) {
            s32 x_offset_byte = U8_AT(sprite_data, -2);
            s32 x_start;
            width = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(x_offset_byte, width);   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
            x_start = -((x_offset_byte << 24) >> 24);
            S16_AT(scratch, 0x80) = x_start;
            S16_AT(scratch, 0x70) = x_start;
            x_end = x_start - width;
        } else {
            s32 x_offset_byte = U8_AT(sprite_data, -2);
            s32 x_start;
            width = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(x_offset_byte, width);   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
            x_start = (x_offset_byte << 24) >> 24;
            S16_AT(scratch, 0x80) = x_start;
            S16_AT(scratch, 0x70) = x_start;
            x_end = x_start + width;
        }
        S16_AT(scratch, 0x88) = x_end;
        S16_AT(scratch, 0x78) = x_end;

        if (sprite[0] & 2) {
            s32 y_offset_byte = U8_AT(sprite_data, -1);
            s32 y_start;
            height = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(y_offset_byte, height);   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
            y_start = -((y_offset_byte << 24) >> 24);
            S16_AT(scratch, 0x7A) = y_start;
            S16_AT(scratch, 0x72) = y_start;
            y_end = y_start - height;
        } else {
            s32 y_offset_byte = U8_AT(sprite_data, -1);
            s32 y_start;
            height = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(y_offset_byte, height);   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
            y_start = (y_offset_byte << 24) >> 24;
            S16_AT(scratch, 0x7A) = y_start;
            S16_AT(scratch, 0x72) = y_start;
            y_end = y_start + height;
        }
        S16_AT(scratch, 0x8A) = y_end;
        S16_AT(scratch, 0x82) = y_end;

        ASM_KEEP(scratch);   /* MATCH pin: slus-diff */
        RotTransSV(scratch + 0x70, prim + 0x08, transform_flag);
        RotTransSV(scratch + 0x78, prim + 0x10, transform_flag);
        RotTransSV(scratch + 0x80, prim + 0x18, transform_flag);
        RotTransSV(scratch + 0x88, prim + 0x20, transform_flag);

        {
            s32 uv_value = U32_AT(scratch, 0x10);
            register s32 u_start ASM_REG("$4") = U32_AT(scratch, 0x08);   /* MATCH pin: slus-diff */
            register s32 v_end ASM_REG("$3") = U32_AT(scratch, 0x14);   /* MATCH pin: slus-diff */
            register s32 v_start ASM_REG("$5") = U32_AT(scratch, 0x0C);   /* MATCH pin: slus-diff */
            uv_value += u_start;
            v_end += v_start;
            U32_AT(scratch, 0x10) = uv_value;
            uv_value = v_start;
            ASM_KEEP_NV(uv_value);   /* MATCH pin: retail keeps tex_start copy the compiler would otherwise drop/add */
            U32_AT(scratch, 0x14) = v_end << 8;
            U32_AT(scratch, 0x0C) = uv_value << 8;
        }

        U16_AT(packet, 0x0A) = U16_AT(sprite_data, 2);
        S16_AT(packet, 0x08) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x10) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x10);
        U16_AT(packet, 0x12) = U16_AT(sprite_data, 0);
        S16_AT(packet, 0x18) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x20) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

        if (S16_AT(packet, 0x04) > S16_AT(packet, 0x1C)) {
            u8 u_end = U8_AT(packet, 0x20);
            U8_AT(packet, 0x20) = u_end + 0xFF;
            U8_AT(packet, 0x10) = u_end;
        }
        if (S16_AT(packet, 0x06) > S16_AT(packet, 0x1E)) {
            u8 v_end = U8_AT(packet, 0x21);
            U8_AT(packet, 0x21) = v_end + 0xFF;
            U8_AT(packet, 0x19) = v_end;
        }

        U8_AT(packet, -1) = 9;
        U8_AT(packet, 3) = 0x2C;
        U8_AT(packet, 2) = 0x80;
        U8_AT(packet, 1) = 0x80;
        U8_AT(packet, 0) = 0x80;
        DrawPrim(prim);
        packet += 0x28;
        prim += 0x28;
        if ((s8)sprite[0] < 0) {
            break;
        }
        sprite_data += 0xC;
        sprite += 0xC;
    } while (1);

    PopMatrix();
    *(u8 **)(contexts[0] + 0x8D0) = prim;
}
