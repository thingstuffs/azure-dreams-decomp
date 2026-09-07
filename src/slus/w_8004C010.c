#include "common.h"

/* CVECTOR-like tint source: r,g,b,cd bytes */
typedef struct S_8004C010 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} S_8004C010;

/* Modulate a 3-byte color (a0) in place by a tint (a1), each channel
 * scaled as (a0[i] * a1[i]) >> 7 and clamped to 0xFF. If the tint is the
 * special "no shading" sentinel (r=g=b=0x80), skip the multiply and
 * return a0 unchanged. Returns a0. */
s32 func_8004C010(u8 *a0, S_8004C010 *a1)
{
    s32 i;
    u8 *p0;
    u8 *p1;
    u32 w;

    w = *(u32 *)a1;
    if ((w << 8) == 0x80808000) {
        return (s32)a0;
    }

    p0 = a0;
    p1 = (u8 *)a1;
    for (i = 0; i < 3;) {
        s32 v = (*p0 * *p1) >> 7;
        if (v < 0x100) {
            *p0 = (u8)v;
        } else {
            *p0 = 0xFF;
        }
        i++;
        p0++;
        p1++;
    }

    return (s32)a0;
}
