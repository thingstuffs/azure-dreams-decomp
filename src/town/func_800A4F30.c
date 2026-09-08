#include "common.h"

typedef struct S_800A2690_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    u8 * unk_14;
} S_800A2690_0;   /* arg0 in func_800A2690 */

typedef struct S_800A2690_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800A2690_1;   /* source in func_800A2690 */

typedef struct S_800A2690_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2690_2;   /* state in func_800A2690 */

typedef struct S_800A2690_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s16 unk_08;
    s16 unk_0A;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    s8 unk_14;
    s8 unk_15;
    s8 unk_16;
    u8 pad_17[0x1];
    s16 unk_18;
} S_800A2690_3;   /* prim in func_800A2690 */

typedef struct S_800A2690_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A2690_4;   /* ((S_800A2690_0 *)arg0)->unk_14 in func_800A2690 */



extern s32 D_800814A0;
extern u8 D_80083160[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666B8(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

/* Advance the effect lifetime and draw a fading, flickering triangle. */
void func_800A2690(void *effect)
{
    u16 angle;
    u16 base_x;
    u16 base_phase_x;
    u16 base_phase_y;
    u16 ticks_left;
    s16 phase_x;
    s16 phase_y;
    s32 center_x;
    s32 fade_wave;
    s32 wave_x2;
    s32 wave_x4;
    s32 wave_x8;
    s32 wave_y2;
    s32 wave_y4;
    s32 wave_y8;
    s32 biased_wave_y2;
    s32 wave_sum;
    s32 intensity;
    s32 draw_page;
    u8 *params;
    u8 *render_state;
    u8 *triangle;
    u8 *draw_packet;

    params = ((S_800A2690_0 *)effect)->unk_14;
    angle = ((S_800A2690_1 *)params)->unk_02;
    base_x = ((S_800A2690_1 *)params)->unk_00;
    base_phase_x = ((S_800A2690_1 *)params)->unk_04;
    ticks_left = ((S_800A2690_0 *)effect)->unk_04 - 1;
    base_phase_y = ((S_800A2690_1 *)params)->unk_06;
    center_x = base_x + ((S_800A2690_0 *)effect)->unk_08 + 0xA0;
    ((S_800A2690_0 *)effect)->unk_04 = ticks_left;
    phase_x = base_phase_x + ((S_800A2690_0 *)effect)->unk_0A;
    phase_y = base_phase_y + ((S_800A2690_0 *)effect)->unk_0C;

    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    } else {
        render_state = *(u8 **)D_80083160;
        triangle = ((S_800A2690_2 *)render_state)->unk_8D0;
        ((S_800A2690_2 *)render_state)->unk_8D0 = triangle + 0x24;

        fade_wave = func_800644B8(((s16)((S_800A2690_0 *)effect)->unk_04 << 11) /
                             ((S_800A2690_0 *)effect)->unk_06);
        intensity = fade_wave / 16;

        wave_x2 = func_800644B8(phase_x * 2);
        wave_x4 = func_800644B8(phase_x * 4);
        wave_x8 = func_800644B8(phase_x * 8);
        wave_y2 = func_800644B8(phase_y * 2);
        wave_y4 = func_800644B8(phase_y * 4);
        wave_y8 = func_800644B8(phase_y * 8);
        wave_sum = wave_x2 + wave_x4 + wave_x8;
        biased_wave_y2 = wave_y2 + 0x2400;
        wave_sum += biased_wave_y2;
        wave_sum += wave_y4;
        wave_sum += wave_y8;
        wave_sum += 0x2400;

        intensity = (intensity * wave_sum) / 36864;
        intensity =
            (intensity * ((S_800A2690_4 *)(((S_800A2690_0 *)effect)->unk_14))->unk_08) / 4096;
        intensity /= 4;

        ((S_800A2690_3 *)triangle)->unk_0E = intensity;
        ((S_800A2690_3 *)triangle)->unk_0D = intensity;
        ((S_800A2690_3 *)triangle)->unk_0C = intensity;
        ((S_800A2690_3 *)triangle)->unk_06 = intensity;
        ((S_800A2690_3 *)triangle)->unk_05 = intensity;
        ((S_800A2690_3 *)triangle)->unk_04 = intensity;
        ((S_800A2690_3 *)triangle)->unk_16 = 0;
        ((S_800A2690_3 *)triangle)->unk_15 = 0;
        ((S_800A2690_3 *)triangle)->unk_14 = 0;
        func_800666B8(triangle);
        func_80066640(triangle, 1);

        ((S_800A2690_3 *)triangle)->unk_08 = center_x - ((S_800A2690_0 *)effect)->unk_10 / 32;
        ((S_800A2690_3 *)triangle)->unk_0A = 0;
        ((S_800A2690_3 *)triangle)->unk_10 = center_x + ((S_800A2690_0 *)effect)->unk_10 / 32;
        ((S_800A2690_3 *)triangle)->unk_12 = 0;
        ((S_800A2690_3 *)triangle)->unk_18 =
            center_x - (((S_800A2690_0 *)effect)->unk_10 * func_800644B8((s16)angle)) / 4096;
        (*(s16 *)((u8 *)triangle + 0x1A)) =
            (((S_800A2690_0 *)effect)->unk_10 * func_80064584((s16)angle)) / 4096;

        render_state = *(u8 **)D_80083160;
        draw_packet = ((S_800A2690_2 *)render_state)->unk_8D0;
        ((S_800A2690_2 *)render_state)->unk_8D0 = draw_packet + 0xC;
        draw_page = func_80066460(0, 0, 0x140, 0);
        func_80067F20(draw_packet, 0, 0, draw_page & 0xFFFF, 0);
        func_8006658C(*(u8 **)D_80083160 + 0xD8, draw_packet);

        func_8006658C(*(u8 **)D_80083160 + 0xD8, triangle);

        render_state = *(u8 **)D_80083160;
        draw_packet = ((S_800A2690_2 *)render_state)->unk_8D0;
        ((S_800A2690_2 *)render_state)->unk_8D0 = draw_packet + 0xC;
        draw_page = func_80066460(0, 1, 0x140, 0);
        func_80067F20(draw_packet, 0, 0, draw_page & 0xFFFF, 0);
        func_8006658C(*(u8 **)D_80083160 + 0xD8, draw_packet);
    }
}
