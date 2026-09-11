#include "common.h"

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
extern void *D_80083160[3];

/* Transform sprite parts into textured quads and add them to the ordering table. */
void func_80044D24(void *unused, void *sprite_data, s32 ot_depth)
{
    u8 **contexts;
    u8 *scratch;
    u8 *sprite;
    void *prim;
    u8 *context;
    u8 *parts;
    register void *matrix ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register void *translation ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register void *part ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register void *packet ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 depth;
    s16 corner_x;
    s16 corner_y;
    u16 flags;
    u16 sprite_x;
    s32 origin_x;
    u8 uv_start;
    u8 uv_size;

    (void)unused;
    context = D_80083160[0];
    sprite = sprite_data;
    scratch = (u8 *)0x1F800000;
    depth = ot_depth;
    contexts = (u8 **)D_80083160;
    do { prim = *(void **)(context + 0x8D0); } while (0);
    U32_AT(scratch, 0x20) = (u32)(context + 0x70);
    U32_AT(scratch, 0x38) = 0x1000;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();

    matrix = scratch + 0x50;
    translation = scratch + 0x40;
    parts = *(u8 **)(sprite + 8);
    flags = U16_AT(sprite, 0x14) | 0x8000;
    U16_AT(sprite, 0x14) = flags;
    U16_AT(scratch, 0x24) = flags;
    part = parts + 1;
    U32_AT(scratch, 0x30) = U16_AT(sprite, 0x1C);
    origin_x = S16_AT(scratch, 0);
    ASM_USE(part);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    packet = (u8 *)prim + 4;
    U32_AT(scratch, 0x34) = U16_AT(sprite, 0x1E);
    sprite_x = U16_AT(sprite, 0x20);
    U32_AT(scratch, 0x40) = origin_x + sprite_x;
    U32_AT(scratch, 0x44) = S16_AT(scratch, 2) + U16_AT(sprite, 0x22);
    TransMatrix(matrix, translation, sprite_x);
    RotMatrix(sprite + 0x16, scratch + 0x50);
    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    SetRotMatrix(scratch + 0x50);
    SetTransMatrix(scratch + 0x50);

    for (;;) {
        if (!(parts[0] & 0x20)) {
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
                s32 offset;
                if (U16_AT(sprite, 0x14) & 0x400) {
                    s32 offset_byte = U8_AT(part, 1);
                    offset = (offset_byte << 24) >> 23;
                } else {
                    s32 offset_byte = U8_AT(part, 1);
                    ASM_KEEP_NV(offset_byte);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    offset = (offset_byte << 24) >> 24;
                }
                {
                    register s32 flipped_offset ASM_REG("$3") = -offset;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP_NV(flipped_offset);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                    S16_AT(scratch, 0x80) = flipped_offset;
                    S16_AT(scratch, 0x70) = flipped_offset;
                    corner_x = flipped_offset - U16_AT(scratch, 0x10);
                }
            } else {
                u16 double_size;
                s32 offset_byte;
                register s32 far_edge ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                s32 offset;
                offset_byte = U8_AT(part, 1);
                offset_byte <<= 24;
                double_size = U16_AT(sprite, 0x14) & 0x400;
                ASM_KEEP_DEP_NV(offset_byte, double_size);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                offset = offset_byte >> 24;
                if (double_size) {
                    offset *= 2;
                }
                S16_AT(scratch, 0x80) = offset;
                S16_AT(scratch, 0x70) = offset;
                far_edge = U16_AT(scratch, 0x10);
                far_edge = offset + far_edge;
                corner_x = far_edge;
            }
            S16_AT(scratch, 0x88) = corner_x;
            S16_AT(scratch, 0x78) = corner_x;

            if ((parts[0] ^ U16_AT(scratch, 0x24)) & 2) {
                s32 offset;
                if (U16_AT(sprite, 0x14) & 0x400) {
                    s32 offset_byte = U8_AT(part, 2);
                    offset = (offset_byte << 24) >> 23;
                } else {
                    s32 offset_byte = U8_AT(part, 2);
                    ASM_KEEP_NV(offset_byte);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    offset = (offset_byte << 24) >> 24;
                }
                {
                    register s32 flipped_offset ASM_REG("$3") = -offset;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP_NV(flipped_offset);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                    S16_AT(scratch, 0x7A) = flipped_offset;
                    S16_AT(scratch, 0x72) = flipped_offset;
                    corner_y = flipped_offset - U16_AT(scratch, 0x14);
                }
            } else {
                u16 double_size;
                s32 offset_byte;
                register s32 far_edge ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                s32 offset;
                offset_byte = U8_AT(part, 2);
                offset_byte <<= 24;
                double_size = U16_AT(sprite, 0x14) & 0x400;
                ASM_KEEP_DEP_NV(offset_byte, double_size);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                offset = offset_byte >> 24;
                if (double_size) {
                    offset *= 2;
                }
                S16_AT(scratch, 0x7A) = offset;
                S16_AT(scratch, 0x72) = offset;
                far_edge = U16_AT(scratch, 0x14);
                far_edge = offset + far_edge;
                corner_y = far_edge;
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
            {
                s32 u_end = U32_AT(scratch, 0x10);
                register s32 u_start ASM_REG("$4") = U32_AT(scratch, 8);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                register s32 v_end ASM_REG("$2") = U32_AT(scratch, 0x14);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                s32 v_start = U32_AT(scratch, 0xC);
                u_end += u_start;
                v_end += v_start;
                v_end <<= 8;
                U32_AT(scratch, 0x14) = v_end;
                {
                    v_end = v_start;
                    ASM_KEEP_NV(v_end);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    U32_AT(scratch, 0x10) = u_end;
                    U32_AT(scratch, 0xC) = v_end << 8;
                }
            }

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
                u16 base_tpage = U16_AT(sprite, 0x10);
                u16 tpage;
                if (base_tpage != 0) {
                    tpage = base_tpage +
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
                register u16 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                prim_code = U8_AT(part, 0);
                sprite[0xF] = prim_code;
                sprite_flags = U16_AT(scratch, 0x24);
                if (sprite_flags & 8) {
                    u8 blend_code;
                    if (sprite_flags & 4) {
                        blend_code = prim_code | 2;
                    } else {
                        blend_code = prim_code & 0xFD;
                    }
                    ASM_KEEP_DEP_NV(blend_code, sprite_flags);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
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
        if ((s8)parts[0] < 0) {
            break;
        }
        parts += 0xC;
    }

    PopMatrix();
    *(void **)(contexts[0] + 0x8D0) = prim;
}
