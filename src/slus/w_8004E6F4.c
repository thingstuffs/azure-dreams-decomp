#include "common.h"

extern s32 DrawSync(s32 mode);
extern void func_8003F80C(void *data, s32 vram, s32 palette, s32 flags);

/* D_8007162C (0x8007162C) is addressed as a literal page + offset pair:
 * gcc 2.6.3 has no TARGET_SPLIT_ADDRESSES, so `&D_8007162C` can only reach
 * the assembler as ONE atomic `la` macro and its lui/addiu halves can never
 * be separated by the two stack-argument loads retail puts between them. */
extern u8 D_8007162C[]; /* 0x8007162C -- referenced as a literal above */

void func_8004E6F4(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, s32 arg5)
{
    register s32 n ASM_REG("$24") = arg5;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s16 colors[16];
    s32 i;
    s32 inv;
    s32 red_a;
    s32 red_b;
    s32 green_a;
    s32 green_b, blue_a;
    register s32 blue_b ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 color;
    s32 t;
    register s32 pad16 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u32 page;
    s32 four;
    register u8 *rowbase ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u8 *row;

    ASM_USE_NV(pad16);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    i = 1;
    colors[0] = 0;
    four = 4;
    page = 0x80070000;
    ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    rowbase = (u8 *)(page + 0x162C);
    row = (u8 *)(arg4 * 8 + (u32)rowbase);
    ASM_USE_NV(row);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    do {
        color = (i < n) << 15;
        if (i < 5) {
            red_a = arg2[0] * row[i - 1];
            inv = four - row[i - 1];
            red_b = arg1[0] * inv;
            green_a = arg2[1] * row[i - 1];
            green_b = arg1[1] * inv;
            blue_a = arg2[2] * row[i - 1];
            blue_b = arg1[2] * inv;
            t = red_a + red_b;
            color += t >> 5;
            t = green_a + green_b;
            color += t & 0x3E0;
        } else {
            red_a = arg3[0] * row[i - 1];
            inv = four - row[i - 1];
            red_b = arg2[0] * inv;
            green_a = arg3[1] * row[i - 1];
            green_b = arg2[1] * inv;
            blue_a = arg3[2] * row[i - 1];
            blue_b = arg2[2] * inv;
            t = red_a + red_b;
            color += t >> 5;
            t = green_a + green_b;
            color += t & 0x3E0;
        }
        t = blue_a + blue_b;
        color += (t & 0x3E0) << 5;
        colors[i] = color;
        i++;
    } while (i < 9);
    func_8003F80C(colors, (arg0 & 0xF) | 0x7D00, 1, 2);
    DrawSync(0);
}
