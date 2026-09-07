#include "common.h"

#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 func_800644B8(s32);
extern s32 rand(void);
extern u8 D_80028868[];
extern s32 D_800814A0;

void func_80026680(void *arg0, void *arg1, void *arg2)
{
    s32 i;
    s32 color;
    register s32 color_temp ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 color_byte ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 color_sub ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s16 mode;
    s16 timer;
    u16 fade;
    u32 next;
    u8 opacity0;
    u8 opacity1;
    void *src;
    void *dst;
    void *link;
    void *color_outer;
    register void *color_inner ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    i = 6;
    do {
        dst = (u8 *)arg0 + (i * 8);
        i--;
        src = (u8 *)arg0 + (i * 8);
        U16_AT(dst, 0x24) = U16_AT(src, 0x24);
        U16_AT(dst, 0x26) = U16_AT(src, 0x26);
        U16_AT(dst, 0x28) = U16_AT(src, 0x28);
    } while (i > 0);

    U16_AT(arg0, 0x24) = U16_AT(arg1, 2);
    U16_AT(arg0, 0x26) = U16_AT(arg1, 6);
    U16_AT(arg0, 0x28) = U16_AT(arg1, 0xA);

    link = PTR_AT(arg0, 8);
    if (link != 0) {
        goto attached;
    }

    mode = S16_AT(arg0, 0x64);
    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    goto common;

mode_zero:
    U16_AT(arg1, 2) += ((S16_AT(PTR_AT(arg0, 0), 2) - S16_AT(arg1, 2)) * 4) /
                       S16_AT(arg0, 0x66);
    U16_AT(arg1, 6) += ((S16_AT(PTR_AT(arg0, 0), 6) - S16_AT(arg1, 6)) * 4) /
                       S16_AT(arg0, 0x66);
    S32_AT(arg1, 8) +=
        (S32_AT(PTR_AT(arg0, 0), 8) -
         (func_800644B8(S16_AT(arg0, 0x66) * 42) << 12) -
         S32_AT(arg1, 8)) /
        S16_AT(arg0, 0x66);

    if (S16_AT(arg0, 0x6A) < 0xC0) {
        U16_AT(arg0, 0x6A) = U16_AT(arg0, 0x6A) + 0x10;
    }
    opacity0 = U8_AT(arg0, 0x6A);
    U8_AT(arg2, 0xD) = opacity0;
    U8_AT(arg2, 0xE) = opacity0;
    U8_AT(arg2, 0xC) = opacity0;

    timer = U16_AT(arg0, 0x66) - 1;
    S16_AT(arg0, 0x66) = timer;
    if (timer > 0) {
        goto common;
    }

    U16_AT(arg1, 2) = U16_AT(PTR_AT(arg0, 0), 2);
    U16_AT(arg1, 6) = U16_AT(PTR_AT(arg0, 0), 6);
    U16_AT(arg1, 0xA) = U16_AT(PTR_AT(arg0, 0), 0xA);
    U16_AT(arg0, 0x64)++;
    goto common;

mode_one:
    link = PTR_AT(arg0, 4);
    if (link != 0) {
        link = PTR_AT(link, -0x14);
        U8_AT(link, 0xC) = ((U16_AT(arg0, 0x68) & 3) * 0x10) + 0x40;
        U8_AT(link, 0xD) = ((U16_AT(arg0, 0x68) & 3) * 0x10) + 0x40;
        U8_AT(link, 0xE) = ((U16_AT(arg0, 0x68) & 3) * 0x10) + 0x40;
    }

    fade = U16_AT(arg0, 0x6A);
    fade = fade - ((s32)(fade << 16) >> 19);
    U16_AT(arg0, 0x6A) = fade;
    opacity1 = U8_AT(arg0, 0x6A);
    U8_AT(arg2, 0xD) = opacity1;
    U8_AT(arg2, 0xE) = opacity1;
    U8_AT(arg2, 0xC) = opacity1;

    if (S16_AT(arg0, 0x6A) < 0x11) {
        U16_AT(arg0, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    goto common;

attached:
    link = (u8 *)link + 0x20;
    U16_AT(arg1, 2) = U16_AT(link, 0x34);
    U16_AT(arg1, 6) = U16_AT(link, 0x36);
    U16_AT(arg1, 0xA) = U16_AT(link, 0x38);

    color_outer = PTR_AT(arg0, 8);
    color_inner = PTR_AT(color_outer, 0xC);
    color_byte = U8_AT(color_inner, 0xC);
    color_sub = U16_AT(arg0, 0x6E);
    color_temp = color_byte - color_sub;
    color = color_temp;
    ASM_KEEP(color_temp);   /* MATCH pin: retail register colouring depends on it */
    if ((s16)color_temp < 0x20) {
        color = 0;
    }

    timer = U16_AT(arg0, 0x66) - 1;
    S16_AT(arg0, 0x66) = timer;
    if ((timer <= 0) && ((s16)color == 0)) {
        U16_AT(arg0, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    U8_AT(arg2, 0xE) = color;
    U8_AT(arg2, 0xD) = color;
    U8_AT(arg2, 0xC) = color;

common:
    S16_AT(arg1, 0xE) = U16_AT(arg0, 0x44) + (rand() & 0xF) - 8;
    S16_AT(arg1, 0x12) = U16_AT(arg0, 0x46) + (rand() & 0xF) - 8;
    S16_AT(arg1, 0x16) = U16_AT(arg0, 0x48) + (rand() & 0xF) - 8;

    next = U32_AT(arg2, 8) + 0xC;
    U32_AT(arg2, 8) = next;
    if ((u32)D_80028868 < next) {
        U32_AT(arg2, 8) = (u32)(D_80028868 - 0x48);
    }
    U16_AT(arg0, 0x68)++;
}
