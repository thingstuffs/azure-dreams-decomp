#include "common.h"


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s32 value;
    u8 pad[8];
} Flags;

s32 func_800644B8(s16);
s32 func_80064584(s16);
void func_800B835C(void *, s32 *, s32, s32);

extern Counter D_80026472;
extern u8 D_80026478[];
extern Flags D_800814A0;


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
    register u16 update_count ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    {
        register s32 base_angle ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 held_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s16 angle;

        update_count = D_80026472.value;
        base_angle = ((S_80025E48_0 *)effect)->unk_22;
        update_count++;
        base_angle <<= 8;
        D_80026472.value = update_count;
        held_angle = base_angle;
        if (((S_80025E48_0 *)effect)->unk_24 != 0) {
            angle = base_angle + (((S_80025E48_0 *)effect)->unk_18.s * 0x10);
            points->unk_02 = ((S_80025E48_0 *)effect)->unk_5C +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
            points->unk_06 = ((S_80025E48_0 *)effect)->unk_5E +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);
            points->unk_0E = ((S_80025E48_0 *)effect)->unk_5C +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
            points->unk_12 = ((S_80025E48_0 *)effect)->unk_5E +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);
        } else {
            angle = held_angle - (((S_80025E48_0 *)effect)->unk_18.s * 0x10);
            points->unk_02 = ((S_80025E48_0 *)effect)->unk_5C +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
            points->unk_06 = ((S_80025E48_0 *)effect)->unk_5E +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);
            points->unk_0E = ((S_80025E48_0 *)effect)->unk_5C +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_80064584(angle)) >> 10);
            points->unk_12 = ((S_80025E48_0 *)effect)->unk_5E +
                ((((S_80025E48_0 *)effect)->unk_66.s * func_800644B8(angle)) >> 10);
        }
    }

    state = ((S_80025E48_0 *)effect)->unk_0A.s;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    {
        s32 color;
        register s32 target_color ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
        target_color = (target_color - color) / fade_frames;
        target_color = color + target_color;
        tint->unk_0D = target_color;
        frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
        ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
        if ((frames_left << 16) > 0) {
            goto epilogue;
        }
        phase_duration = 0x18;
        phase = ((S_80025E48_0 *)effect)->unk_0A.u;
        ((S_80025E48_0 *)effect)->unk_1A.u = phase_duration;
        ((S_80025E48_0 *)effect)->unk_0A.u = phase + 1;
        return;
    }

state_1:
    {
        register u16 rise_speed ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        u16 frames_left;
        u16 phase;
        s32 phase_duration;

        points->unk_16 +=
            (s32)(((S_80025E48_0 *)effect)->unk_26 << 16) >> 17;
        rise_speed = ((S_80025E48_0 *)effect)->unk_26 + 1;
        frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
        ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
        ((S_80025E48_0 *)effect)->unk_26 = rise_speed;
        if ((frames_left << 16) > 0) {
            goto epilogue;
        }
        phase = ((S_80025E48_0 *)effect)->unk_0A.u;
        phase_duration = 0x10;
        ((S_80025E48_0 *)effect)->unk_1A.u = phase_duration;
        ((S_80025E48_0 *)effect)->unk_0A.u = phase + 1;
        return;
    }

state_2:
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
            goto epilogue;
        }
        ((S_80025E48_0 *)effect)->unk_1A.u = 8;
        ((S_80025E48_0 *)effect)->unk_0A.u++;
        return;
    }

state_3:
    {
        u8 *glow;
        s32 glow_color;
        register s32 color ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
        if (((S_80025E48_0 *)effect)->unk_24 == 0) {
            goto fade_slow;
        }

fade_fast:
        color = tint->unk_0D;
        fade_step = color /
            (((S_80025E48_0 *)effect)->unk_1A.s - 6);
        color -= fade_step;
        tint->unk_0D = color;
        frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
        ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
        if ((s16)frames_left < 7) {
            goto finish;
        }
        goto epilogue;

fade_slow:
        color = tint->unk_0D;
        fade_step = color /
            ((S_80025E48_0 *)effect)->unk_1A.s;
        color -= fade_step;
        tint->unk_0D = color;
        frames_left = ((S_80025E48_0 *)effect)->unk_1A.u - 1;
        ((S_80025E48_0 *)effect)->unk_1A.u = frames_left;
        if ((frames_left << 16) > 0) {
            goto epilogue;
        }

finish:
        ((S_80025E48_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

epilogue:
    return;
}
