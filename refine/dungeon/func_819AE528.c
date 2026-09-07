#include "common.h"

typedef struct S_80025D28_0 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    u16 unk_30;
    u8 pad_32[0x2];
    u16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x4];
    s16 unk_3E;
    s16 unk_40;
} S_80025D28_0;   /* arg0 in func_80025D28 */

typedef struct S_80025D28_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025D28_1;   /* arg1 in func_80025D28 */

typedef struct S_80025D28_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025D28_2;   /* arg2 in func_80025D28 */



extern s32 func_800644B8();
extern s32 func_80064584();
extern u8 D_80027452[16];
extern s32 D_800814A0;

/* Update two animated points, fade their intensity, and flag expiration. */
void func_80025D28(void *state, void *points, void *appearance) {
    s32 phase_angle;
    s32 phase_step;
    s32 side_offset_x;
    s32 side_offset_y;
    s32 radial_offset_x;
    s32 radial_offset_y;
    s32 start_wave_x;
    s32 start_wave_y;
    s32 direction_x;
    s32 direction_y;
    s32 end_wave_x;
    s32 end_wave_y;
    s32 side_direction_x;
    s32 side_direction_y;
    u16 ticks_left;
    u8 intensity;

    phase_step = ((S_80025D28_0 *)state)->unk_38;
    phase_angle = (s16)(phase_step << 6);
    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    start_wave_x = func_800644B8(phase_angle);
    ((S_80025D28_1 *)points)->unk_00 = (((S_80025D28_0 *)state)->unk_1C << 0x10) +
        ((s32)(start_wave_x * func_80064584(((S_80025D28_0 *)state)->unk_36 + 0x400) * ((S_80025D28_0 *)state)->unk_3E) >> 7);
    start_wave_y = func_800644B8(phase_angle);
    ((S_80025D28_1 *)points)->unk_04 = (((S_80025D28_0 *)state)->unk_1E << 0x10) +
        ((s32)(start_wave_y * func_800644B8(((S_80025D28_0 *)state)->unk_36 + 0x400) * ((S_80025D28_0 *)state)->unk_3E) >> 7);
    ((S_80025D28_1 *)points)->unk_08 = (((S_80025D28_0 *)state)->unk_20 << 0x10) +
        ((func_80064584(phase_angle) * ((S_80025D28_0 *)state)->unk_3E) << 5);
    end_wave_x = func_800644B8(phase_angle);
    direction_x = func_80064584(((S_80025D28_0 *)state)->unk_36 + 0x400);
    side_direction_x = func_80064584(((S_80025D28_0 *)state)->unk_36 + 0x800);
    radial_offset_x = end_wave_x * direction_x;
    radial_offset_x *= ((S_80025D28_0 *)state)->unk_3E;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    side_offset_x = side_direction_x * ((S_80025D28_0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_0C = (((S_80025D28_0 *)state)->unk_1C << 0x10) +
        (radial_offset_x >> 7) + (side_offset_x << 6);
    end_wave_y = func_800644B8(phase_angle, side_offset_x);
    direction_y = func_800644B8(((S_80025D28_0 *)state)->unk_36 + 0x400);
    side_direction_y = func_800644B8(((S_80025D28_0 *)state)->unk_36 + 0x800);
    radial_offset_y = end_wave_y * direction_y;
    radial_offset_y *= ((S_80025D28_0 *)state)->unk_3E;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    side_offset_y = side_direction_y * ((S_80025D28_0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_10 = (((S_80025D28_0 *)state)->unk_1E << 0x10) +
        (radial_offset_y >> 7) + (side_offset_y << 6);
    ((S_80025D28_1 *)points)->unk_14 = (((S_80025D28_0 *)state)->unk_20 << 0x10) +
        ((func_80064584(phase_angle, side_offset_y) * ((S_80025D28_0 *)state)->unk_3E) << 5);
    ((S_80025D28_0 *)state)->unk_40 = (u16)((S_80025D28_0 *)state)->unk_40 + 2;
    ((S_80025D28_0 *)state)->unk_38 = (u16)((S_80025D28_0 *)state)->unk_38 + 1;
    intensity = ((S_80025D28_2 *)appearance)->unk_0D;
    ((S_80025D28_2 *)appearance)->unk_0D = intensity - (intensity >> 3);
    ticks_left = ((S_80025D28_0 *)state)->unk_30 - 1;
    ((S_80025D28_0 *)state)->unk_30 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    ((S_80025D28_0 *)state)->unk_34 = ((S_80025D28_0 *)state)->unk_34 + 1;
}

/* MECHANISM: Natural long-lived arguments and results produce the retail 0x30 frame and s5/s4/s3/s2/s1/s0 roles.
   A short raw signed-load local selects lh before the shift/truncation while preserving phase_angle in s1.
   Zero-operand scheduling barriers after both chained products reproduce retail multiply/mflo emission order. */
