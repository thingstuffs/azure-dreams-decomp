#include "common.h"

extern void func_800A8CA8(void *, s32, s32, s32);
extern void func_800A8EE8(void *);
extern s32 func_800B28A0(void);
extern s32 D_80083160;
extern s32 D_800D0E48[];
extern s32 D_80100E30;

/* Draws a closed ring of shaded quads using evenly spaced angular samples. */
void func_800A9358(s32 shape, s32 source)
{
    u32 *scratch;
    register volatile s32 segment ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *count_base;
    s32 angle_sum;
    s32 saved_source;
    s32 saved_shape;
    u32 *call_scratch;
    register s32 angle ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 call_source ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_shape ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 *segment_counts;
    register u32 first_color ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 first_inner_xy ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 first_middle_xy ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u32 first_outer_xy;   /* MATCH pin: keeps a constant in a register as retail does */
    register u32 next_color ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 next_inner_xy ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 next_middle_xy ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 next_outer_xy;
    s32 more_segments;
    u32 closing_depth;
    register u32 closing_color ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    s32 count_index;
    s32 segment_count;
    u32 ot_addr;
    volatile u32 saved_color[1];
    u32 saved_inner_xy;
    u32 saved_middle_xy;
    u32 saved_outer_xy;   /* MATCH pin: retail schedule: same instructions, different order without it */

    saved_shape = shape;
    ASM_KEEP_NV(saved_shape);   /* MATCH pin: keeps a statement from moving across a call/branch */
    saved_source = source;
    ASM_KEEP_NV(saved_source);   /* MATCH pin: load-bearing for the whole function shape */
    angle_sum = 0;
    ASM_KEEP_NV(angle_sum);   /* MATCH pin: load-bearing for the whole function shape */
    count_index = func_800B28A0();
    call_scratch = (u32 *)0x1F800000;
    ASM_KEEP_NV(call_scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    angle = 0;
    ASM_KEEP_NV(angle);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_source = saved_source;
    call_shape = saved_shape;
    segment_counts = D_800D0E48;
    ASM_KEEP_NV(segment_counts);   /* MATCH pin: retail immediate-load split depends on it */
    segment_count = segment_counts[count_index];
    ASM_KEEP_NV(segment_count);   /* MATCH pin: retail immediate-load split depends on it */
    count_base = (u8 *)0x80100000;
    ASM_KEEP_NV(count_base);   /* MATCH pin: keeps a constant in a register as retail does */
    *(s32 *)(count_base + 0xE30) = segment_count;
    ot_addr = D_80083160;
    ASM_KEEP_NV(ot_addr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = call_scratch;
    ASM_KEEP_NV(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ot_addr += 0xB0;
    scratch[0x24 / 4] = ot_addr;
    func_800A8CA8((void *)call_scratch, angle, call_source, call_shape);
    segment = 0;
    first_color = scratch[0x114 / 4];
    first_inner_xy = scratch[0xE8 / 4];
    first_middle_xy = scratch[0xEC / 4];
    first_outer_xy = scratch[0x124 / 4];
    saved_inner_xy = first_inner_xy;
    saved_middle_xy = first_middle_xy;
    scratch[0x118 / 4] = first_color;
    scratch[0xF0 / 4] = first_inner_xy;
    scratch[0xF4 / 4] = first_middle_xy;
    scratch[0x128 / 4] = first_outer_xy;
    saved_color[-1] = first_color;
    saved_outer_xy = first_outer_xy;

    if ((*(s32 *)(count_base + 0xE30) - 1) > 0) {
        do {
            angle = 0x1000;
            angle = angle / *(s32 *)(count_base + 0xE30);
            angle = angle_sum + angle;
            angle_sum = angle;
            ASM_KEEP_NV(angle);   /* MATCH pin: retail schedule: same instructions, different order without it */
            func_800A8CA8((void *)scratch, (s16)angle,
                          saved_source, saved_shape);
            if (scratch[0xC4 / 4] < 0x1E0U) {
                func_800A8EE8((void *)scratch);
            }
            segment++;
            next_color = scratch[0x114 / 4];
            next_inner_xy = scratch[0xE8 / 4];
            next_middle_xy = scratch[0xEC / 4];
            more_segments = *(s32 *)(count_base + 0xE30);
            next_outer_xy = scratch[0x124 / 4];
            more_segments -= 1;
            more_segments = segment < more_segments;
            scratch[0x118 / 4] = next_color;
            scratch[0xF0 / 4] = next_inner_xy;
            scratch[0xF4 / 4] = next_middle_xy;
            scratch[0x128 / 4] = next_outer_xy;
        } while (more_segments);
    }

    angle = 0x1000;
    func_800A8CA8((void *)scratch,
                  (s16)(angle_sum + (angle / D_80100E30)),
                  saved_source, saved_shape);
    closing_depth = scratch[0xC4 / 4];
    ASM_KEEP_NV(closing_depth);   /* MATCH pin: retail schedule: same instructions, different order without it */
    closing_color = saved_color[-1];
    ASM_KEEP_NV(closing_color);   /* MATCH pin: retail schedule: same instructions, different order without it */
    closing_depth = closing_depth < 0x1E0U;
    scratch[0x114 / 4] = closing_color;
    scratch[0xE8 / 4] = saved_inner_xy;
    scratch[0xEC / 4] = saved_middle_xy;
    scratch[0x124 / 4] = saved_outer_xy;
    if (closing_depth) {
        func_800A8EE8((void *)scratch);
    }
}
