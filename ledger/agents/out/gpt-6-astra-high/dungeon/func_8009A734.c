#include "common.h"

extern s32 func_8009A540(s32, s32, s32, s16);
extern s32 func_8009FB34(s32, s32, ...);
extern s16 func_800A0818(s32, s32, s32, s32, void *);

/* Checks distinct neighboring positions for equal values or a successful fallback check. */
s32 func_8009FE94(s32 x0, s32 y0, s32 check_param, s32 x1, volatile s32 y1) {
    register s32 raw_x0 ASM_REG("$6") = x0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 raw_y0 ASM_REG("$8") = y0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 axis_delta;
    register s32 held_x1 ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 loaded_y1;
    register s32 held_y1 ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 dx;
    s32 dy;
    s32 x_adjacent;
    s32 x1_short;
    s32 y1_short;
    s32 source_value;
    s32 target_value;
    s32 query_aux;

    ASM_KEEP_NV(raw_x0);   /* MATCH pin: retail register colouring depends on it */
    ASM_KEEP_NV(raw_y0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    held_x1 = x1;
    ASM_KEEP_NV(held_x1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    x1_short = (s16)x1;
    axis_delta = x1_short - (s16)x0;
    dx = __builtin_abs(axis_delta);
    x_adjacent = dx < 2;
    loaded_y1 = y1;
    held_y1 = loaded_y1;
    if (!x_adjacent) goto reject;
    y1_short = (s16)loaded_y1;
    axis_delta = y1_short - (s16)y0;
    dy = __builtin_abs(axis_delta);
    if (dy >= 2 || dx + dy == 0) goto reject;
    source_value = func_8009FB34(raw_x0 & 0xFFFF, raw_y0 & 0xFFFF, raw_x0, x1 << 16);
    target_value = func_8009FB34(held_x1 & 0xFFFF, held_y1 & 0xFFFF);
    if ((source_value << 16) == (target_value << 16)) {
        return 1;
    }
    {
        s32 check_result_hi;
        check_result_hi = (func_8009A540(((func_800A0818((s16)x0, (s16)y0, x1_short, y1_short, &query_aux) << 16) >> 25) & 0xFFFF, (s16)x0, (s16)y0, (s16)(check_param - 0x20))) << 16;
        if (check_result_hi != 0) {
            return 1;
        }
    }
reject:
    return 0;
}
