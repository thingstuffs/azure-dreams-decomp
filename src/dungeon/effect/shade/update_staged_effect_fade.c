#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/shade.h"
#include "sdk/libgte.h"
#include "dungeon/effect/shade/staged_fade_data.h"

#include "dungeon/effect/screen.h"
#include "dungeon/data.h"

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

/* Update the effect position, staged motion, and color fades, then mark completion. */
void update_staged_effect_fade(EffectObjectGroupsBody *effect, S_80025E48_1 *points, SpriteFrameState *tint)
{
    GpuRectBuffer draw_params;
    s16 state;
    s16 angle;
    s32 base_angle;
    s32 held_angle;

    base_angle = effect->object_index << 8;
    held_angle = base_angle;
    staged_fade_count++;
    if (effect->group_index != 0) {
        angle = base_angle + effect->spin_angle.s * 0x10;
    } else {
        angle = held_angle - effect->spin_angle.s * 0x10;
    }
    points->unk_02 = effect->center_x +
        ((effect->radius.s * rcos(angle)) >> 10);
    points->unk_06 = effect->center_y +
        ((effect->radius.s * rsin(angle)) >> 10);
    points->unk_0E = effect->center_x +
        ((effect->radius.s * rcos(angle)) >> 10);
    points->unk_12 = effect->center_y +
        ((effect->radius.s * rsin(angle)) >> 10);

    state = effect->stage.s;
    switch (state) {
    case 0:
        {
            s32 color;
            s32 target_color;
            s32 fade_frames;
            s32 phase_duration;
            u16 phase;
            u16 frames_left;

            if (effect->max_radius.s > effect->radius.s) {
                effect->radius.u++;
                color = tint->color.c.g;
            } else {
                color = tint->color.c.g;
            }
            target_color = effect->group_index;
            fade_frames = effect->stage_ticks.s;
            if (target_color != 0) {
                target_color = 0xF0;
            } else {
                target_color = 0x20;
            }
            tint->color.c.g = ((s32)(color + ((s32)((target_color - color) / fade_frames))));
            frames_left = effect->stage_ticks.u - 1;
            effect->stage_ticks.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            phase_duration = 0x18;
            phase = effect->stage.u;
            effect->stage_ticks.u = phase_duration;
            effect->stage.u = phase + 1;
            return;
        }

    case 1:
        {
            u16 frames_left;

            points->unk_16 += (s16)effect->rise_step >> 1;
            effect->rise_step++;
            frames_left = effect->stage_ticks.u - 1;
            effect->stage_ticks.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            effect->stage_ticks.u = 0x10;
            effect->stage.u++;
            return;
        }

    case 2:
        {
            u8 *glow;
            s32 glow_color;
            s32 color_step;
            u16 frames_left;

            if ((effect->group_index == 0) &&
                (effect->object_index == 0)) {
                glow = staged_glow_data;
                glow_color = glow[0xC];
                color_step = (0x14 - glow_color) / effect->stage_ticks.s;
                draw_params.words[0] = 0x01000340;
                draw_params.words[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                draw_textured_ellipse(glow, &draw_params.rect, 1, 0);
            }
            frames_left = effect->stage_ticks.u - 1;
            effect->stage_ticks.u = frames_left;
            if ((frames_left << 16) > 0) {
                return;
            }
            effect->stage_ticks.u = 8;
            effect->stage.u++;
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
                effect->stage_ticks.s;
            angle_step = effect->spin_speed;
            effect->spin_speed = angle_step + 1;
            effect->spin_angle.u += angle_step;
            effect->radius.u +=
                (((s32)(effect->max_radius.u << 16) >> 17) -
                 effect->radius.s) / effect->stage_ticks.s;

            if ((effect->group_index == 0) &&
                (effect->object_index == 0)) {
                glow = staged_glow_data;
                glow_color = glow[0xC];
                color_step = (0x10 - glow_color) /
                    effect->stage_ticks.s;
                draw_params.words[0] = 0x01000340;
                draw_params.words[1] = 0x00200020;
                glow_color += color_step;
                glow[0xC] = glow_color;
                glow[0xD] = glow_color;
                draw_textured_ellipse(glow, &draw_params.rect, 1, 0);
            }
            if (effect->group_index != 0) {
                fast_color = tint->color.c.g;
                fade_step = fast_color /
                    (effect->stage_ticks.s - 6);
                fast_color -= fade_step;
                tint->color.c.g = fast_color;
                frames_left = effect->stage_ticks.u - 1;
                effect->stage_ticks.u = frames_left;
                if ((s16)frames_left >= 7) {
                    return;
                }
            } else {
                slow_color = tint->color.c.g;
                fade_step = slow_color /
                    effect->stage_ticks.s;
                slow_color -= fade_step;
                tint->color.c.g = slow_color;
                frames_left = effect->stage_ticks.u - 1;
                effect->stage_ticks.u = frames_left;
                if ((frames_left << 16) > 0) {
                    return;
                }
            }

            NODE_HEADER(effect)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }

    }
    return;
}
