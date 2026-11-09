#include "shared/object_node.h"
#include "dungeon/monster/kid.h"
#include "common.h"
#include "shared/object_flags.h"


/* Animate primitive colors and mark the effect finished when its timer expires. */
void animate_effect_colors(RandomlyRotatedOffsetEffectBody *effect_state, ObjectPosition *unused, SpriteFrameState *primitive_arg)
{
    RandomlyRotatedOffsetEffectBody *state = effect_state;
    s16 frames_left;
    s32 scaled_color;
    s32 color_step;
    u8 color;
    SpriteFrameState *primitive = primitive_arg;

    primitive->angle_z += 0x320;

    if (state->unk_1A.s >= 0x33) {
        primitive->color.c.r = (state->unk_00.u * (0x41 - state->unk_1A.s)) / 14;
        primitive->color.c.g = (state->unk_01.u * (0x41 - state->unk_1A.s)) / 14;
        primitive->color.c.b = (state->unk_02.u * (0x41 - state->unk_1A.s)) / 14;
    } else if (state->unk_1A.s < 0x1A) {
        if (state->unk_1A.s >= 0x10) {
            color_step = (state->unk_00.u - state->unk_01.u) / (state->unk_1A.s - 0xF);
            color = state->unk_01.u + color_step;
            state->unk_01.u = color;
            primitive->color.c.g = color;

            color_step = (state->unk_00.u - state->unk_02.u) / (state->unk_1A.s - 0xF);
            color = state->unk_02.u + color_step;
            state->unk_02.u = color;
            primitive->color.c.b = color;
        } else if (state->unk_1A.s >= 8) {
            scaled_color = state->unk_00.u * (state->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->color.c.r = scaled_color >> 3;

            scaled_color = state->unk_01.u * (state->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->color.c.g = scaled_color >> 3;

            scaled_color = state->unk_02.u * (state->unk_1A.s - 8);
            primitive->color.c.b = scaled_color / 8;
        } else {
            state->unk_1A.s = 0;
        }
    }

    frames_left = state->unk_1A.u - 1;
    state->unk_1A.s = frames_left;
    if ((frames_left << 16) <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
