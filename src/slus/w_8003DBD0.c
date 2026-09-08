#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void RotTransSV(void *v0, void *out, void *flag);
extern s32 rcos(s32);
extern s32 rsin(s32);
extern void *D_80083160[3];

void func_8003DBD0(void *arg0, void *arg1, void *arg2)
{
    register u8 *out ASM_REG("$19");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u8 *g;
    u8 *scratch;
    s32 c4;
    s32 c6;
    s32 c8;
    s32 ang;
    s32 ex;
    s32 ey;
    s32 dx;
    s32 dy;
    s32 h0;
    s32 h2;
    s32 n4;
    s32 n8;
    s32 nb;

    out = (u8 *)arg2;
    g = (u8 *)D_80083160;
    PushMatrix();
    scratch = (u8 *)0x1F800000;

    c4 = S16_AT(g, 0xC4);
    c6 = S16_AT(g, 0xC6);
    c8 = S16_AT(g, 0xC8);
    U32_AT(scratch, 0x30) = c4;
    U32_AT(scratch, 0x34) = c6;
    U32_AT(scratch, 0x38) = c8;
    ang = U16_AT(arg0, 0x16) - 0x400;
    U16_AT(scratch, 0x100) = ang - U16_AT(scratch, 0x30);
    U16_AT(scratch, 0x104) = U16_AT(g, 0xB8) + (U16_AT(arg0, 0x1A) - U16_AT(scratch, 0x34));
    U16_AT(scratch, 0x102) = U16_AT(arg0, 0x18);
    ex = U16_AT(arg0, 0x20);
    U32_AT(scratch, 0xE4) = ex;
    U16_AT(scratch, 0x108) = ex;
    ey = U16_AT(arg0, 0x22);
    U32_AT(scratch, 0xEC) = 0;
    U32_AT(scratch, 0xE8) = ey;
    U16_AT(scratch, 0x10A) = ey;
    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);

    U32_AT(scratch, 0x30) = U16_AT(arg0, 0x1C) << 1;
    U32_AT(scratch, 0x34) = U16_AT(arg0, 0x1E) << 1;
    U32_AT(scratch, 0x38) = 0x2000;
    ScaleMatrix((void *)0x1F8000D0, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    U16_AT(scratch, 0x24) = U16_AT(arg0, 0x14);

    if ((U8_AT(arg1, 0) ^ U16_AT(scratch, 0x24)) & 1) {
        s32 raw = U8_AT(arg1, 2);
        dx = U16_AT(scratch, 0x108);
        ASM_KEEP_DEP_NV(raw, dx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x70) = -((raw << 24) >> 24) - dx;
    } else {
        s32 raw = U8_AT(arg1, 2);
        dx = U16_AT(scratch, 0x108);
        ASM_KEEP_DEP_NV(raw, dx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x70) = ((raw << 24) >> 24) - dx;
    }

    if ((U8_AT(arg1, 0) ^ U16_AT(scratch, 0x24)) & 2) {
        s32 raw = U8_AT(arg1, 3);
        dy = U16_AT(scratch, 0x10A);
        ASM_KEEP_DEP_NV(raw, dy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x74) = -((raw << 24) >> 24) - dy;
    } else {
        s32 raw = U8_AT(arg1, 3);
        dy = U16_AT(scratch, 0x10A);
        ASM_KEEP_DEP_NV(raw, dy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x74) = ((raw << 24) >> 24) - dy;
    }
    S16_AT(scratch, 0x72) = 0;
    RotTransSV((void *)((u32)scratch | 0x70), out, (void *)((u32)scratch | 0x94));

    h0 = U16_AT(out, 0);
    U16_AT(scratch, 0x00) = h0;
    n4 = S16_AT(g, 0xC4);
    h2 = U16_AT(out, 2);
    U32_AT(scratch, 0x30) = -n4;
    n8 = S16_AT(g, 0xC8);
    nb = S16_AT(g, 0xB8);
    U16_AT(scratch, 0x02) = h2;
    U32_AT(scratch, 0x38) = nb - n8;
    U16_AT(out, 4) += ((s32)(s16)U16_AT(scratch, 0x02) * rcos(U32_AT(scratch, 0x30))) >> 12;
    S16_AT(out, 0) = (S16_AT(scratch, 0x00) * rcos(U32_AT(scratch, 0x38))) >> 12;
    S16_AT(out, 2) = (S16_AT(scratch, 0x00) * rsin(U32_AT(scratch, 0x38))) >> 12;
    PopMatrix();
}
