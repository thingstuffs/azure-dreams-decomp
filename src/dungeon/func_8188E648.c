#include "common.h"
#include "shared/object_flags.h"


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

s32 func_800644B8(s16);
s32 func_80064584(s16);
void func_800B835C(void *, s32 *, s32, s32);

extern Counter D_80026472;
extern u8 D_80026478[];


typedef struct S_80025E48_0_pre {
    u16 unk_00;
} S_80025E48_0_pre;   /* the 0x2 bytes before arg0 in func_80025E48, addressed as arg0[-1] */

typedef struct S_80025E48_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xC];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
    s16 unk_24;
    u16 unk_26;
    u8 pad_28[0x34];
    u16 unk_5C;
    u16 unk_5E;
    u8 pad_60[0x4];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    union { s16 s; u16 u; } unk_66;   /* accessed as both */
} S_80025E48_0;   /* arg0 in func_80025E48 */

typedef struct S_80025E48_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80025E48_1;   /* arg1 in func_80025E48 */

typedef struct S_80025E48_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025E48_2;   /* arg2 in func_80025E48 */

/* Update the effect position, staged motion, and color fades, then mark completion. */
void func_80025E48(void *effect, S_80025E48_1 *points, S_80025E48_2 *tint)
{
    s32 draw_params[2];
    s16 state;
    s16 angle;
    s32 base_angle;
    s32 held_angle;

    base_angle = ((S_80025E48_0 *)effect)->unk_22 << 8;
    held_angle = base_angle;
    D_80026472.value++;
    if (((S_80025E48_0 *)effect)->unk_24 != 0) {
        angle = base_angle + ((S_80025E48_0 *)effect)->unk_18.s * 0x10;
    } else {
        angle = held_angle - ((S_80025E48_0 *)effect)->unk_18.s * 0x10;
    }
    points->unk_02 = ((S_80025E48_0 *)effect)->unk_5C +
        ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
    points->unk_06 = ((S_80025E48_0 *)effect)->unk_5E +
        ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);
    points->unk_0E = ((S_80025E48_0 *)effect)->unk_5C +
        ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
    points->unk_12 = ((S_80025E48_0 *)effect)->unk_5E +
        ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);

    state = ((S_80025E48_0 *)effect)->unk_0A.s;
    switch (state) {
    case 0:
        {
            s32 color;
            s32 target_color;
            s32 fade_frames;
            s32 phase_duration;
            u16 phase;
            u16 frames_left;

            if (((S_80025E48_0 *)effect)->unk_64.s > ((S_80025E48_0 *)effect)->unk_66.s) {
                ((S_80025E48_0 *)effect)->unk_66.u++;
                color = tint->unk_0D;
            } else {
                color = tint->unk_0D;
            }
            target_color = ((S_80025E48_0 *)effect)->unk_24;
            fade_frames = ((S_80025E48_0 *)effect)->unk_1A.s;
            if (target_color != 0) {
                target_color = 0xF0;
            } else {
                target_color = 0x20;
            }
            tint->unk_0D = ((s32)(color + ((s32)((target_color - color) / fade_frames))));
            frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
            ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            phase_duration = 0x18;
            phase = ((S_80025E48_0 *)effect)->unk_0A.u;
            ((S_80025E48_0 *)effect)->unk_1A.u = phase_duration;
            ((S_80025E48_0 *)effect)->unk_0A.u = phase + 1;
            return;
        }

    case 1:
        {
            u16 frames_left;

            points->unk_16 += (s16)((S_80025E48_0 *)effect)->unk_26 >> 1;
            ((S_80025E48_0 *)effect)->unk_26++;
            frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
            ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            ((S_80025E48_0 *)effect)->unk_1A.u = 0x10;
            ((S_80025E48_0 *)effect)->unk_0A.u++;
            return;
        }

    case 2:
        {
            u8 *glow;
            s32 glow_color;
            s32 color_step;
            u16 frames_left;

            if ((((S_80025E48_0 *)effect)->unk_24 == 0) &&
                (((S_80025E48_0 *)effect)->unk_22 == 0)) {
                glow = D_80026478;
                glow_color = glow[0xC];
                color_step = (0x14 - glow_color) / ((S_80025E48_0 *)effect)->unk_1A.s;
                draw_params[0] = 0x01000340;
                draw_params[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                func_800B835C(glow, draw_params, 1, 0);
            }
            frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
            ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            ((S_80025E48_0 *)effect)->unk_1A.u = 8;
            ((S_80025E48_0 *)effect)->unk_0A.u++;
            return;
        }

    case 3:
        {
            u8 *glow;
            s32 glow_color;
            s32 fast_color;
            s32 slow_color;
            s16 fade_step;
            s32 color_step;
            u16 angle_step;
            u16 frames_left;

            points->unk_0A +=
                (points->unk_16 - points->unk_0A) /
                ((S_80025E48_0 *)effect)->unk_1A.s;
            angle_step = ((S_80025E48_0 *)effect)->unk_1C;
            ((S_80025E48_0 *)effect)->unk_1C = angle_step + 1;
            ((S_80025E48_0 *)effect)->unk_18.u += angle_step;
            ((S_80025E48_0 *)effect)->unk_66.u +=
                (((s32)(((S_80025E48_0 *)effect)->unk_64.u << 16) >> 17) -
                 ((S_80025E48_0 *)effect)->unk_66.s) / ((S_80025E48_0 *)effect)->unk_1A.s;

            if ((((S_80025E48_0 *)effect)->unk_24 == 0) &&
                (((S_80025E48_0 *)effect)->unk_22 == 0)) {
                glow = D_80026478;
                glow_color = glow[0xC];
                color_step = (0x10 - glow_color) /
                    ((S_80025E48_0 *)effect)->unk_1A.s;
                draw_params[0] = 0x01000340;
                draw_params[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                func_800B835C(glow, draw_params, 1, 0);
            }
            if (((S_80025E48_0 *)effect)->unk_24 != 0) {
                fast_color = tint->unk_0D;
                fade_step = fast_color /
                    (((S_80025E48_0 *)effect)->unk_1A.s - 6);
                fast_color -= fade_step;
                tint->unk_0D = fast_color;
                frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
                ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
                if ((s16)frames_left >= 7) {
                    return;
                }
            } else {
                slow_color = tint->unk_0D;
                fade_step = slow_color /
                    ((S_80025E48_0 *)effect)->unk_1A.s;
                slow_color -= fade_step;
                tint->unk_0D = slow_color;
                frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
                ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
                if ((frames_left << 16) > 0) {
                    return;
                }
            }

            ((S_80025E48_0_pre *)effect)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }

    }
    return;
}
