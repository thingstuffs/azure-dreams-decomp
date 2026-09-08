#include "common.h"

extern u8 *D_800E3D7C;
extern u16 D_8008347E;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

extern void func_8003DB4C(void *, s32);
extern s32 func_80065F90(s32, s32);
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_800A0134(void *, void *);
extern s32 func_800A0548(s32, s32);
extern s32 func_800BCB04(s32, s32, s32);

s32 func_8009B88C(u8 *arg0, s32 arg1, s32 arg2, s16 *out_x, s16 *out_y) {
    u16 info;
    u8 *spad;
    u16 tmp;
    u8 *state;
    s32 x8;
    u8 *obj;
    s32 ox;
    s32 oy;
    u16 *xp;
    u16 *yp;
    u16 *xp2;
    u16 *yp2;
    s32 xv;
    s32 yv;
    s32 xa;
    s32 ya;
    s32 xb;
    s32 yb;
    s32 xc;
    s32 yc;
    s32 dtx;
    s32 dty;
    s32 dx;
    s32 dist;
    s32 dy;
    s32 idx;
    s32 j;
    s32 j2;
    s16 count;
    s32 x0;
    s32 y0;
    s32 y8;
    s32 x16;
    s32 y16;
    s32 first;
    register s32 fl ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    spad = (u8 *)0x1F800000;
    if (arg0 != 0) {
        state = arg0;
        first = 0;
    } else {
        state = D_800E3D7C;
        first = 1;
        arg0 = *(u8 **)(state + 88) + 32;
    }
    func_8003DB4C(spad, 7);
    goto loop_tail;

    do {
    obj = *(u8 **)(arg0 - 20);
    ox = *(u8 *)(obj + 36);
    oy = *(u8 *)(obj + 37);
    dtx = (s16)arg1 - ox;
    dx = __builtin_abs(dtx);
    dty = (s16)arg2 - oy;
    dy = __builtin_abs(dty);
    first = 0;
    if (dx < dy) {
        dx = dy;
    }
    if (dx < 3) {
        if (dx == 0) {
            idx = 0;
        } else if (dx == 1) {
            idx = (((func_80065F90(oy - (s16)arg2, ox - (s16)arg1) + 256) >> 9) & 7) + 1;
        } else {
            idx = (((func_80065F90(oy - (s16)arg2, ox - (s16)arg1) + 128) >> 8) & 15) + 9;
        }
        dist = (s16)func_800A0134(state, arg0);
        if (dist < 0) {
            dist = -dist;
        }
        if (dist < 64) {
            *(u8 *)((u32)idx | (u32)spad) = 1;
        }
    }

loop_tail:
    arg0 = *(u8 **)(arg0 + 92) + 32;
    } while (arg0 != state || (fl = first) != 0);
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (spad[0] != 0) {
        goto search;
    }
    x0 = (s16)arg1;
    y0 = (s16)arg2;
    if (func_800A0548(x0, y0) != 0) {
        goto search;
    }
    if ((func_8009A350((s16)(arg1 - 1), y0, 0, &info) << 16) == 0) {
        goto search;
    }
    if ((info & 0x8000) != 0) {
        goto search;
    }
    if ((info & 0x400) != 0 && (*(u32 *)(arg0 + 28) & 0x40000) == 0) {
        goto search;
    }
    if ((s16)func_800BCB04((((x0 << 6) + 32) & 0xffe0), (((y0 << 6) + 32) & 0xffe0),
                           (s16)(*(u16 *)(state + 136) - 32)) >= 512) {
        goto search;
    }
    *out_x = arg1;
    *out_y = arg2;
    return 1;

found8:
    xv = xp[0];
    *out_x = arg1 + xv;
    yv = yp[0];
    *out_y = arg2 + yv;
    return 1;

found16:
    xv = xp2[0];
    *out_x = arg1 + xv;
    yv = yp2[0];
    *out_y = arg2 + yv;
    return 1;

search:
    count = 0;
    x8 = (s16)arg1;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    tmp = D_8008347E;
    y8 = (s16)arg2;
    ASM_USE(y8);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    idx = tmp & 7;
    do {
        j = idx;
        ASM_KEEP_NV(j);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_USE2(arg1, arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(arg1, arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(arg2, arg2);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        if (*(spad + j + 1) == 0) {
            xp = D_8006CCD8 + j;
            yp = D_8006CCE8 + j;
            ASM_USE(yp);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if ((xa = xp[0], ya = yp[0],
                 func_800A0548((s16)(arg1 + xa), (s16)(arg2 + ya))) == 0 &&
                (func_8009A350(x8, y8, j, &info) << 16) != 0 &&
                (info & 0x8000) == 0 &&
                ((info & 0x400) == 0 || (*(u32 *)(arg0 + 28) & 0x40000) != 0) &&
                (s16)func_800BCB04((((x8 + (s16)xp[0]) << 6) + 32) & 0xffe0,
                                   (((y8 + (s16)yp[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(state + 136) - 32)) < 512) {
                goto found8;
            }
        }
        count++;
        idx = (idx + 1) & 7;
    } while (count < 8);

    count = 0;
    x16 = (s16)arg1;
    tmp = D_8008347E;
    y16 = (s16)arg2;
    idx = tmp & 15;
    do {
        j2 = idx;
        ASM_KEEP_NV(j2);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_USE2(arg1, arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(arg2, arg2);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        if (*(spad + j2 + 9) == 0) {
            xp2 = D_800DCE6C + j2;
            yp2 = D_800DCE8C + j2;
            ASM_USE(yp2);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if ((xb = xp2[0], yb = yp2[0],
                 func_800A0548((s16)(arg1 + xb), (s16)(arg2 + yb))) == 0 &&
                ((xc = xp2[0], yc = yp2[0],
                  func_8009A350((s16)(arg1 + xc - 1), (s16)(arg2 + yc), 0, &info)) << 16) != 0 &&
                (info & 0x8000) == 0 &&
                ((info & 0x400) == 0 || (*(u32 *)(arg0 + 28) & 0x40000) != 0) &&
                (s16)func_800BCB04((((x16 + (s16)xp2[0]) << 6) + 32) & 0xffe0,
                                   (((y16 + (s16)yp2[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(state + 136) - 32)) < 512) {
                goto found16;
            }
        }
        count++;
        idx = (idx + 1) & 15;
    } while (count < 16);
    ASM_USE_NV(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    return 0;
}
