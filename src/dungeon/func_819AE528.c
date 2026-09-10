#include "common.h"
#include "records/Rec_func_80025D28_arg0.h"


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

    phase_step = ((Rec_func_80025D28_arg0 *)state)->unk_38;
    phase_angle = (s16)(phase_step << 6);
    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    start_wave_x = func_800644B8(phase_angle);
    ((S_80025D28_1 *)points)->unk_00 = (((Rec_func_80025D28_arg0 *)state)->unk_1C << 0x10) +
        ((s32)(start_wave_x * func_80064584(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) >> 7);
    start_wave_y = func_800644B8(phase_angle);
    ((S_80025D28_1 *)points)->unk_04 = (((Rec_func_80025D28_arg0 *)state)->unk_1E << 0x10) +
        ((s32)(start_wave_y * func_800644B8(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) >> 7);
    ((S_80025D28_1 *)points)->unk_08 = (((Rec_func_80025D28_arg0 *)state)->unk_20 << 0x10) +
        ((func_80064584(phase_angle) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) << 5);
    end_wave_x = func_800644B8(phase_angle);
    direction_x = func_80064584(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400);
    side_direction_x = func_80064584(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x800);
    radial_offset_x = end_wave_x * direction_x;
    do {
        radial_offset_x *= ((Rec_func_80025D28_arg0 *)state)->unk_3E;
    } while (0);
    side_offset_x = side_direction_x * ((Rec_func_80025D28_arg0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_0C = (((Rec_func_80025D28_arg0 *)state)->unk_1C << 0x10) +
        (radial_offset_x >> 7) + (side_offset_x << 6);
    end_wave_y = func_800644B8(phase_angle, side_offset_x);
    direction_y = func_800644B8(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x400);
    side_direction_y = func_800644B8(((Rec_func_80025D28_arg0 *)state)->unk_36 + 0x800);
    radial_offset_y = end_wave_y * direction_y;
    do {
        radial_offset_y *= ((Rec_func_80025D28_arg0 *)state)->unk_3E;
    } while (0);
    side_offset_y = side_direction_y * ((Rec_func_80025D28_arg0 *)state)->unk_40;
    ((S_80025D28_1 *)points)->unk_10 = (((Rec_func_80025D28_arg0 *)state)->unk_1E << 0x10) +
        (radial_offset_y >> 7) + (side_offset_y << 6);
    ((S_80025D28_1 *)points)->unk_14 = (((Rec_func_80025D28_arg0 *)state)->unk_20 << 0x10) +
        ((func_80064584(phase_angle, side_offset_y) * ((Rec_func_80025D28_arg0 *)state)->unk_3E) << 5);
    ((Rec_func_80025D28_arg0 *)state)->unk_40 = (u16)((Rec_func_80025D28_arg0 *)state)->unk_40 + 2;
    ((Rec_func_80025D28_arg0 *)state)->unk_38 = (u16)((Rec_func_80025D28_arg0 *)state)->unk_38 + 1;
    intensity = ((S_80025D28_2 *)appearance)->unk_0D;
    ((S_80025D28_2 *)appearance)->unk_0D = intensity - (intensity >> 3);
    ticks_left = ((Rec_func_80025D28_arg0 *)state)->unk_30 - 1;
    ((Rec_func_80025D28_arg0 *)state)->unk_30 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    ((Rec_func_80025D28_arg0 *)state)->unk_34 = ((Rec_func_80025D28_arg0 *)state)->unk_34 + 1;
}

/* MECHANISM: Natural long-lived arguments and results produce the retail 0x30 frame and s5/s4/s3/s2/s1/s0 roles.
   A short raw signed-load local selects lh before the shift/truncation while preserving phase_angle in s1.
   Zero-operand scheduling barriers after both chained products reproduce retail multiply/mflo emission order. */
