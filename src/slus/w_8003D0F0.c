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

void func_8003D0F0(void)
{
    u8 *scratch;
    register u8 *packet ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register u8 *record ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *prim;
    u8 *script;
    u8 *flag;
    u8 **root;
    u8 *context;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;

    flag = (u8 *)0x1F800094;
    context = (u8 *)D_80083160[0];
    scratch = (u8 *)0x1F800000;
    prim = *(u8 **)(context + 0x8D0);
    root = (u8 **)D_80083160;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();

    script = D_800777AC;
    U32_AT(scratch, 0x40) = 0x100;
    U32_AT(scratch, 0x44) = 0xB0;
    U16_AT(scratch, 0x28) = 0;
    U16_AT(scratch, 0x2A) = 0;
    U16_AT(scratch, 0x2C) = 0;
    TransMatrix((void *)0x1F800050, (void *)0x1F800040);
    RotMatrix((void *)0x1F800028, (void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);
    SetTransMatrix((void *)0x1F800050);
    record = script + 4;
    packet = prim + 4;

    do {
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

        if (script[0] & 1) {
            s32 raw = U8_AT(record, -2);
            s32 v;
            dx = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(raw, dx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = -((raw << 24) >> 24);
            S16_AT(scratch, 0x80) = v;
            S16_AT(scratch, 0x70) = v;
            x = v - dx;
        } else {
            s32 raw = U8_AT(record, -2);
            s32 v;
            dx = U16_AT(scratch, 0x10);
            ASM_KEEP_DEP_NV(raw, dx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = (raw << 24) >> 24;
            S16_AT(scratch, 0x80) = v;
            S16_AT(scratch, 0x70) = v;
            x = v + dx;
        }
        S16_AT(scratch, 0x88) = x;
        S16_AT(scratch, 0x78) = x;

        if (script[0] & 2) {
            s32 raw = U8_AT(record, -1);
            s32 v;
            dy = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(raw, dy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = -((raw << 24) >> 24);
            S16_AT(scratch, 0x7A) = v;
            S16_AT(scratch, 0x72) = v;
            y = v - dy;
        } else {
            s32 raw = U8_AT(record, -1);
            s32 v;
            dy = U16_AT(scratch, 0x14);
            ASM_KEEP_DEP_NV(raw, dy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            v = (raw << 24) >> 24;
            S16_AT(scratch, 0x7A) = v;
            S16_AT(scratch, 0x72) = v;
            y = v + dy;
        }
        S16_AT(scratch, 0x8A) = y;
        S16_AT(scratch, 0x82) = y;

        ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        RotTransSV(scratch + 0x70, prim + 0x08, flag);
        RotTransSV(scratch + 0x78, prim + 0x10, flag);
        RotTransSV(scratch + 0x80, prim + 0x18, flag);
        RotTransSV(scratch + 0x88, prim + 0x20, flag);

        {
            s32 sum_x = U32_AT(scratch, 0x10);
            register s32 base_x ASM_REG("$4") = U32_AT(scratch, 0x08);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register s32 sum_y ASM_REG("$3") = U32_AT(scratch, 0x14);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register s32 base_y ASM_REG("$5") = U32_AT(scratch, 0x0C);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            sum_x += base_x;
            sum_y += base_y;
            U32_AT(scratch, 0x10) = sum_x;
            sum_x = base_y;
            ASM_KEEP_NV(sum_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            U32_AT(scratch, 0x14) = sum_y << 8;
            U32_AT(scratch, 0x0C) = sum_x << 8;
        }

        U16_AT(packet, 0x0A) = U16_AT(record, 2);
        S16_AT(packet, 0x08) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x10) = U16_AT(scratch, 0x0C) + U16_AT(scratch, 0x10);
        U16_AT(packet, 0x12) = U16_AT(record, 0);
        S16_AT(packet, 0x18) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x08);
        S16_AT(packet, 0x20) = U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

        if (S16_AT(packet, 0x04) > S16_AT(packet, 0x1C)) {
            u8 shade = U8_AT(packet, 0x20);
            U8_AT(packet, 0x20) = shade + 0xFF;
            U8_AT(packet, 0x10) = shade;
        }
        if (S16_AT(packet, 0x06) > S16_AT(packet, 0x1E)) {
            u8 shade = U8_AT(packet, 0x21);
            U8_AT(packet, 0x21) = shade + 0xFF;
            U8_AT(packet, 0x19) = shade;
        }

        U8_AT(packet, -1) = 9;
        U8_AT(packet, 3) = 0x2C;
        U8_AT(packet, 2) = 0x80;
        U8_AT(packet, 1) = 0x80;
        U8_AT(packet, 0) = 0x80;
        DrawPrim(prim);
        packet += 0x28;
        prim += 0x28;
        if ((s8)script[0] < 0) {
            break;
        }
        record += 0xC;
        script += 0xC;
    } while (1);

    PopMatrix();
    *(u8 **)(root[0] + 0x8D0) = prim;
}
