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

void func_8003CCB0(s32 arg0)
{
    u8 *scratch;
    register u8 *packet ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register u8 *record ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *prim;
    u8 *flag;
    s32 i;
    u8 buf[2];
    u8 **root;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    s32 off;
    s32 shade;
    s32 colour;
    register u8 *in0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register u8 *out0 ASM_REG("$5");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register u8 *arg2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    scratch = (u8 *)0x1F800000;
    root = (u8 **)D_80083160;

    if (D_80080AAC == 0) {
        u8 *ent;
        s32 fill;
        u8 *src;
        i = 0;
        src = D_8006CDB8;
        fill = -4;
        ent = D_80083798;
        D_80080AAC = D_80080AAC + 1;
        buf[1] = 0;
        do {
            register u8 *made ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            buf[0] = *(u8 *)(i + (u32)src);
            made = (u8 *)func_8004E298(ent, buf, 0);
            S8_AT(made, 3) = fill;
            S8_AT(made, 2) = fill;
            if (i == 0) {
                D_80080AB0 = made;
            }
            i++;
            ent += 0xC;
        } while (i < 0xE);
    }

    prim = *(u8 **)(root[0] + 0x8D0);
    i = 0;
    flag = scratch + 0x94;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();
    {
        register u8 *rec0 ASM_REG("$3") = (u8 *)D_80080AB0;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        record = rec0 + 4;
    }
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    packet = prim + 7;

    do {
        off = i << 2;
        {
            s32 base1 = *(s16 *)((u8 *)D_80083858 + off);
            s32 delta1 = *(s16 *)((u8 *)D_80083858 + 4 + off);
            U32_AT(scratch, 0x40) = base1 + ((delta1 - base1) * arg0) / 8;
        }
        {
            s32 base2 = *(s16 *)((u8 *)D_800838D8 + off);
            s32 delta2 = *(s16 *)((u8 *)D_800838D8 + 4 + off);
            U32_AT(scratch, 0x44) = base2 + ((delta2 - base2) * arg0) / 8;
        }
        TransMatrix(scratch + 0x50, scratch + 0x40);
        RotMatrix(scratch + 0x28, scratch + 0x50);
        SetRotMatrix(scratch + 0x50);
        SetTransMatrix(scratch + 0x50);

        a = U8_AT(record, 4);
        U32_AT(scratch, 0x08) = a;
        b = U8_AT(record, 6);
        U32_AT(scratch, 0x10) = b;
        if (a + b >= 0x100) {
            U32_AT(scratch, 0x10) = b - 1;
        }
        a = U8_AT(record, 5);
        U32_AT(scratch, 0x0C) = a;
        b = U8_AT(record, 7);
        U32_AT(scratch, 0x14) = b;
        if (a + b >= 0x100) {
            U32_AT(scratch, 0x14) = b - 1;
        }

        in0 = scratch + 0x70;
        out0 = prim + 0x08;
        arg2 = flag;
        {
            s32 raw = U8_AT(record, -2);
            s32 v;
            x = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(raw, x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = (raw << 24) >> 24;
            S16_AT(scratch, 0x80) = v;
            S16_AT(scratch, 0x70) = v;
            v = v + x;
            S16_AT(scratch, 0x88) = v;
            S16_AT(scratch, 0x78) = v;
        }
        {
            s32 raw = U8_AT(record, -1);
            s32 v;
            y = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(raw, y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = (raw << 24) >> 24;
            S16_AT(scratch, 0x7A) = v;
            S16_AT(scratch, 0x72) = v;
            v = v + y;
            S16_AT(scratch, 0x8A) = v;
            S16_AT(scratch, 0x82) = v;
        }

        RotTransSV(in0, out0, arg2);
        RotTransSV(scratch + 0x78, prim + 0x10, flag);
        RotTransSV(scratch + 0x80, prim + 0x18, flag);
        RotTransSV(scratch + 0x88, prim + 0x20, flag);

        {
            s32 sum_x = U32_AT(scratch, 0x10);
            register s32 base_x ASM_REG("$4") = U32_AT(scratch, 0x08);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register s32 sum_y ASM_REG("$3") = U32_AT(scratch, 0x14);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            register s32 base_y ASM_REG("$5") = U32_AT(scratch, 0x0C);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            sum_x += base_x;
            sum_y += base_y;
            U32_AT(scratch, 0x10) = sum_x;
            sum_x = base_y;
            ASM_KEEP_NV(sum_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            U32_AT(scratch, 0x14) = sum_y << 8;
            U32_AT(scratch, 0x0C) = sum_x << 8;
        }

        U16_AT(packet, 0x07) = U16_AT(record, 2);
        S16_AT(packet, 0x05) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x0D) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x10);
        U16_AT(packet, 0x0F) = U16_AT(record, 0);
        S16_AT(packet, 0x15) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x1D) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

        if (S16_AT(packet, 0x01) > S16_AT(packet, 0x19)) {
            u8 sh = U8_AT(packet, 0x1D);
            U8_AT(packet, 0x1D) = sh + 0xFF;
            U8_AT(packet, 0x0D) = sh;
        }
        if (S16_AT(packet, 0x03) > S16_AT(packet, 0x1B)) {
            u8 sh = U8_AT(packet, 0x1E);
            U8_AT(packet, 0x1E) = sh + 0xFF;
            U8_AT(packet, 0x16) = sh;
        }
        U8_AT(packet, -4) = 9;
        U8_AT(packet, 0) = 0x2C;

        {
            s32 tmpv = (rsin((D_80080AA4 << 8) + (i << 6)) >> 6) + 0x80;
            s32 half = arg0 / 2;
            shade = tmpv >> half;
        }
        U8_AT(packet, -3) = shade;
        colour = 0;
        if (D_80080AA8 == 0) {
            colour = shade;
        }
        {
            u8 *cur = prim;
            prim += 0x28;
            record += 0xC;
            i++;
            U8_AT(packet, -1) = colour;
            U8_AT(packet, -2) = colour;
            U8_AT(packet, 0) |= 2;
            DrawPrim(cur);
        }
        packet += 0x28;
    } while (i < 0xE);

    PopMatrix();
    {
        *(u8 **)(root[0] + 0x8D0) = prim;
    }
}
