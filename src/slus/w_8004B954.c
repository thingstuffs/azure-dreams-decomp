#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct {
    s16 vx;
    s16 vy;
} DVEC;

extern s32 func_8004C010(void *a, void *b);
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);

void *func_8004B954(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4,
                    s32 *arg5, s32 arg6)
{
    DVEC pos;
    s32 basex;
    s32 dx;
    s32 step;
    s32 i;
    s32 j;
    register s32 ang ASM_REG("$18");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 basey;
    s32 cnt;
    s32 dy;
    register u8 *src ASM_REG("$20");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u8 *dst14;
    u8 *dst1c;
    register u8 *m ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 f;
    u32 t14;

    i = 1;
    src = (u8 *)arg2;
    dst14 = src;
    dx = S16_AT(dst14, 0x10) - S16_AT(dst14, 0x08);
    dy = S16_AT(dst14, 0x22) - S16_AT(dst14, 0x0A);
    f = U8_AT(arg4, 0);
    dst1c = src;
    if (!(f & 0x20)) {
        cnt = 0x10;
        if (f & 0x10) {
            cnt = 0x20;
        }
    } else {
        cnt = 0x40;
    }
    step = 0x1000 / cnt;
    f = U8_AT(arg4, 0);
    if (f & 0x40) {
        if (f & 1) {
            i += 0x400;
            basex = S16_AT(arg2, 0x08) - dx;
        } else {
            basex = S16_AT(arg2, 0x08);
        }
        if (U8_AT(arg4, 0) & 2) {
            i += 0x800;
            {
                s32 ty = S16_AT(arg2, 0x0A);
                basey = ty - dy;
            }
        } else {
            basey = S16_AT(arg2, 0x0A);
        }
        cnt = cnt / 4;
    } else {
        dy = dy >> 1;
        dx = dx >> 1;
        basex = S16_AT(arg2, 0x08) + dx;
        {
            s32 ty2 = S16_AT(arg2, 0x0A);
            basey = ty2 + dy;
        }
    }

    if (dx != 0 && dy != 0) {
        pos.vx = ((rcos(0) * dx) >> 12) + basex;
        {
            s32 py = (rsin(0) * dy) >> 12;
            pos.vy = py + basey;
        }
        S16_AT(dst1c, 0x08) = S8_AT(arg4, 0x08) + basex;
        S16_AT(dst1c, 0x0A) = S8_AT(arg4, 0x09) + basey;
        if (arg6 == 0) {
            U8_AT(dst1c, 0x03) = 4;
        } else {
            U8_AT(dst1c, 0x03) = 6;
        }
        m = dst1c + 4;
        U32_AT(arg2, 0x04) = U32_AT(arg4, 0x04);
        func_8004C010(m, arg0);
        func_8004C010(m, arg1);
        U8_AT(dst1c, 0x07) = U8_AT(arg4, 0x01) & 0x7F;
        m = dst1c + 0xC;
        if (arg6 != 0) {
            arg3 = (void *)((u8 *)arg3 + 0xC);
            U32_AT(dst1c, 0x0C) = U32_AT(arg3, 0);
            func_8004C010(m, arg0);
            func_8004C010(m, arg1);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            U32_AT(dst1c, 0x14) = U32_AT(dst1c, 0x0C);
            m = dst1c + 0x18;
            j = i;
            if (j <= i + cnt) {
                ang = j * step;
                do {
                    U32_AT(dst1c, 0x00) = U32_AT(src, 0x00);
                    U32_AT(m, -0x14) = U32_AT(src, 0x04);
                    U32_AT(m, -0x10) = U32_AT(src, 0x08);
                    U32_AT(m, -0x0C) = U32_AT(src, 0x0C);
                    t14 = U32_AT(src, 0x14);
                    U32_AT(m, -0x08) = *(u32 *)&pos;
                    U32_AT(m, -0x04) = t14;
                    pos.vx = ((rcos(ang) * dx) >> 12) + basex;
                    j++;
                    dst1c += 0x1C;
                    {
                        s32 py = (rsin(ang) * dy) >> 12;
                        pos.vy = py + basey;
                    }
                    ang += step;
                    U32_AT(m, 0x00) = *(u32 *)&pos;
                    m += 0x1C;
                } while (j <= i + cnt);
            }
        } else {
            j = i;
            m = dst14 + 0x10;
            if (j <= i + cnt) {
                ang = j * step;
                do {
                    U32_AT(dst14, 0x00) = U32_AT(src, 0x00);
                    U32_AT(m, -0x0C) = U32_AT(src, 0x04);
                    t14 = U32_AT(src, 0x08);
                    U32_AT(m, -0x04) = *(u32 *)&pos;
                    U32_AT(m, -0x08) = t14;
                    pos.vx = ((rcos(ang) * dx) >> 12) + basex;
                    j++;
                    dst14 += 0x14;
                    {
                        s32 py = (rsin(ang) * dy) >> 12;
                        pos.vy = py + basey;
                    }
                    ang += step;
                    U32_AT(m, 0x00) = *(u32 *)&pos;
                    m += 0x14;
                } while (j <= i + cnt);
            }
        }
        *arg5 = cnt;
    } else {
        if (arg6 != 0) {
            arg3 = (void *)((u8 *)arg3 + 0xC);
        }
        *arg5 = 0;
    }
    return arg3;
}
