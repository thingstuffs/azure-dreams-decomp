#include "common.h"
#include "shared/game_work.h"

extern void func_800A8CA8(void *, s32, s32, s32);
extern void func_800A8EE8(void *);
extern s32 func_800B28A0(void);
extern s32 D_800D0E48[];
extern s32 D_80100E30;

/* Draws a closed ring of shaded quads using evenly spaced angular samples. */
void func_800A9358(s32 shape, s32 source)
{
    u32 *scratch;
    s32 segment;
    s16 angle_sum;
    s16 angle;
    u32 saved_outer_xy;
    u32 saved_inner_xy;
    u32 saved_middle_xy;
    u32 saved_color;

    angle_sum = 0;
    scratch = (u32 *)0x1F800000;
    D_80100E30 = D_800D0E48[func_800B28A0()];
    scratch[0x24 / 4] = (s32)gameWork.unk_000 + 0xB0;
    func_800A8CA8(scratch, 0, source, shape);
    saved_color = scratch[0x118 / 4] = scratch[0x114 / 4];
    saved_inner_xy = scratch[0xF0 / 4] = scratch[0xE8 / 4];
    saved_middle_xy = scratch[0xF4 / 4] = scratch[0xEC / 4];
    saved_outer_xy = scratch[0x128 / 4] = scratch[0x124 / 4];

    for (segment = 0; segment < D_80100E30 - 1; segment++) {
        angle = angle_sum + 0x1000 / D_80100E30;
        angle_sum = angle;
        func_800A8CA8(scratch, angle, source, shape);
        if (scratch[0xC4 / 4] < 0x1E0U) {
            func_800A8EE8(scratch);
        }
        scratch[0x118 / 4] = scratch[0x114 / 4];
        scratch[0xF0 / 4] = scratch[0xE8 / 4];
        scratch[0xF4 / 4] = scratch[0xEC / 4];
        scratch[0x128 / 4] = scratch[0x124 / 4];
    }

    angle = angle_sum + 0x1000 / D_80100E30;
    func_800A8CA8(scratch, angle, source, shape);
    scratch[0x114 / 4] = saved_color;
    scratch[0xE8 / 4] = saved_inner_xy;
    scratch[0xEC / 4] = saved_middle_xy;
    scratch[0x124 / 4] = saved_outer_xy;
    if (scratch[0xC4 / 4] < 0x1E0U) {
        func_800A8EE8(scratch);
    }
}
