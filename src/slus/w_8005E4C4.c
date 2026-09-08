#include "common.h"

extern volatile u16 D_80086BD0[];
extern volatile u16 *D_80079958;
extern s32 D_80079950;
extern volatile s32 D_8007951C;

u32 func_8005E4C4(s32 mode, u32 val, s32 i0, s32 i1)
{
    u32 old;
    s32 one;

    {
        register volatile u16 *p ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        u32 hi;
        u32 lo;

        if (D_80079950 & 1) {
            p = D_80086BD0;
        } else {
            p = D_80079958;
        }
        hi = (p[i1] & 0xFF) << 16;
        lo = p[i0];
        ASM_USE2_NV(one, hi);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        one = 1;
        old = lo | hi;
    }

    switch (mode) {
    case 1:
        if (D_80079950 & 1) {
            volatile u16 *q = D_80086BD0;
            q[i0] |= val;
            q[i1] |= (val >> 16) & 0xFF;
            D_8007951C |= one << ((i0 - 0xC6) >> 1);
        } else {
            volatile u16 *r = D_80079958;
            r[i0] |= val;
            r[i1] |= (val >> 16) & 0xFF;
        }
        old |= val & 0xFFFFFF;
        break;

    case 0:
        if (D_80079950 & 1) {
            volatile u16 *q = D_80086BD0;
            q[i0] &= ~val;
            q[i1] &= ~((val >> 16) & 0xFF);
            D_8007951C |= one << ((i0 - 0xC6) >> 1);
        } else {
            volatile u16 *r = D_80079958;
            r[i0] &= ~val;
            r[i1] &= ~((val >> 16) & 0xFF);
        }
        old &= ~(val & 0xFFFFFF);
        break;

    case 8:
        if (D_80079950 & 1) {
            volatile u16 *q = D_80086BD0;
            q[i0] = val;
            q[i1] = (val >> 16) & 0xFF;
            D_8007951C |= one << ((i0 - 0xC6) >> 1);
        } else {
            volatile u16 *r = D_80079958;
            r[i0] = val;
            r[i1] = (val >> 16) & 0xFF;
        }
        old = val & 0xFFFFFF;
        break;
    }
    return old & 0xFFFFFF;
}
