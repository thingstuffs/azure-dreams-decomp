#include "common.h"

extern s32 func_8009A540(s32, s32, s32, s16);
extern s32 func_8009FB34(s32, s32, ...);
extern s16 func_800A0818(s32, s32, s32, s32, void *);

s32 func_8009FE94(s32 x0, s32 y0, s32 arg2, s32 x1, volatile s32 y1) {
    register s32 raw_x0 ASM_REG("$6") = x0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 raw_y0 ASM_REG("$8") = y0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 dx_raw;
    register s32 held_x1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 loaded_y1;
    register s32 held_y1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 dx;
    s32 dy;
    s32 dx_small;
    s32 x1_short;
    s32 y1_short;
    s32 first;
    s32 second;
    s32 scratch;

    ASM_KEEP_NV(raw_x0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(raw_y0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    held_x1 = x1;
    ASM_KEEP_NV(held_x1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    x1_short = (s16)x1;
    dx_raw = x1_short - (s16)x0;
    dx = __builtin_abs(dx_raw);
    dx_small = dx < 2;
    loaded_y1 = y1;
    held_y1 = loaded_y1;
    if (!dx_small) goto ret_0;
    y1_short = (s16)loaded_y1;
    dx_raw = y1_short - (s16)y0;
    dy = __builtin_abs(dx_raw);
    if (dy >= 2 || dx + dy == 0) goto ret_0;
    first = func_8009FB34(raw_x0 & 0xFFFF, raw_y0 & 0xFFFF, raw_x0, x1 << 16);
    second = func_8009FB34(held_x1 & 0xFFFF, held_y1 & 0xFFFF);
    if ((first << 16) == (second << 16)) {
        return 1;
    }
    {
        s32 v1_val;
        v1_val = (func_8009A540(((func_800A0818((s16)x0, (s16)y0, x1_short, y1_short, &scratch) << 16) >> 25) & 0xFFFF, (s16)x0, (s16)y0, (s16)(arg2 - 0x20))) << 16;
        if (v1_val != 0) {
            return 1;
        }
    }
ret_0:
    return 0;
}
