#include "common.h"
#include "shared/object_flags.h"


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

s32 rsin(s16);
s32 rcos(s16);
#include "dungeon/effect/screen.h"

extern Counter staged_fade_count;
extern u8 staged_glow_data[];


typedef struct S_80025E48_0_pre {
    u16 unk_00;
} S_80025E48_0_pre;   /* the 0x2 bytes before arg0 in update_staged_effect_fade, addressed as arg0[-1] */


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
} S_80025E48_1;   /* arg1 in update_staged_effect_fade */

typedef struct S_80025E48_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025E48_2;   /* arg2 in update_staged_effect_fade */

/* Update the effect position, staged motion, and color fades, then mark completion. */
void update_staged_effect_fade(EffectObjectGroupsBody *effect, S_80025E48_1 *points, S_80025E48_2 *tint)
{
    GpuRectBuffer draw_params;
    s16 state;
    s16 angle;
    s32 base_angle;
    s32 held_angle;

    base_angle = effect->unk_22 << 8;
    held_angle = base_angle;
    staged_fade_count.value++;
    if (effect->unk_24 != 0) {
        angle = base_angle + effect->unk_18.s * 0x10;
    } else {
        angle = held_angle - effect->unk_18.s * 0x10;
    }
    points->unk_02 = effect->unk_5C +
        ((effect->unk_66.s * rcos(angle)) >> 10);
    points->unk_06 = effect->unk_5E +
        ((effect->unk_66.s * rsin(angle)) >> 10);
    points->unk_0E = effect->unk_5C +
        ((effect->unk_66.s * rcos(angle)) >> 10);
    points->unk_12 = effect->unk_5E +
        ((effect->unk_66.s * rsin(angle)) >> 10);

    state = effect->unk_0A.s;
    switch (state) {
    case 0:
        {
            s32 color;
            s32 target_color;
            s32 fade_frames;
            s32 phase_duration;
            u16 phase;
            u16 frames_left;

            if (effect->unk_64.s > effect->unk_66.s) {
                effect->unk_66.u++;
                color = tint->unk_0D;
            } else {
                color = tint->unk_0D;
            }
            target_color = effect->unk_24;
            fade_frames = effect->unk_1A.s;
            if (target_color != 0) {
                target_color = 0xF0;
            } else {
                target_color = 0x20;
            }
            tint->unk_0D = ((s32)(color + ((s32)((target_color - color) / fade_frames))));
            frames_left = effect->unk_1A.u - 1;
            effect->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            phase_duration = 0x18;
            phase = effect->unk_0A.u;
            effect->unk_1A.u = phase_duration;
            effect->unk_0A.u = phase + 1;
            return;
        }

    case 1:
        {
            u16 frames_left;

            points->unk_16 += (s16)effect->unk_26 >> 1;
            effect->unk_26++;
            frames_left = effect->unk_1A.u - 1;
            effect->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            effect->unk_1A.u = 0x10;
            effect->unk_0A.u++;
            return;
        }

    case 2:
        {
            u8 *glow;
            s32 glow_color;
            s32 color_step;
            u16 frames_left;

            if ((effect->unk_24 == 0) &&
                (effect->unk_22 == 0)) {
                glow = staged_glow_data;
                glow_color = glow[0xC];
                color_step = (0x14 - glow_color) / effect->unk_1A.s;
                draw_params.words[0] = 0x01000340;
                draw_params.words[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                draw_textured_ellipse(glow, &draw_params.rect, 1, 0);
            }
            frames_left = effect->unk_1A.u - 1;
            effect->unk_1A.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            effect->unk_1A.u = 8;
            effect->unk_0A.u++;
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
                effect->unk_1A.s;
            angle_step = effect->unk_1C;
            effect->unk_1C = angle_step + 1;
            effect->unk_18.u += angle_step;
            effect->unk_66.u +=
                (((s32)(effect->unk_64.u << 16) >> 17) -
                 effect->unk_66.s) / effect->unk_1A.s;

            if ((effect->unk_24 == 0) &&
                (effect->unk_22 == 0)) {
                glow = staged_glow_data;
                glow_color = glow[0xC];
                color_step = (0x10 - glow_color) /
                    effect->unk_1A.s;
                draw_params.words[0] = 0x01000340;
                draw_params.words[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                draw_textured_ellipse(glow, &draw_params.rect, 1, 0);
            }
            if (effect->unk_24 != 0) {
                fast_color = tint->unk_0D;
                fade_step = fast_color /
                    (effect->unk_1A.s - 6);
                fast_color -= fade_step;
                tint->unk_0D = fast_color;
                frames_left = effect->unk_1A.u - 1;
                effect->unk_1A.u = frames_left;
                if ((s16)frames_left >= 7) {
                    return;
                }
            } else {
                slow_color = tint->unk_0D;
                fade_step = slow_color /
                    effect->unk_1A.s;
                slow_color -= fade_step;
                tint->unk_0D = slow_color;
                frames_left = effect->unk_1A.u - 1;
                effect->unk_1A.u = frames_left;
                if ((frames_left << 16) > 0) {
                    return;
                }
            }

            ((S_80025E48_0_pre *)effect)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }

    }
    return;
}
