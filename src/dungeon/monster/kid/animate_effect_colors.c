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

    if (state->lifetime.s >= 0x33) {
        primitive->color.c.r = (state->red.u * (0x41 - state->lifetime.s)) / 14;
        primitive->color.c.g = (state->green.u * (0x41 - state->lifetime.s)) / 14;
        primitive->color.c.b = (state->blue.u * (0x41 - state->lifetime.s)) / 14;
    } else if (state->lifetime.s < 0x1A) {
        if (state->lifetime.s >= 0x10) {
            color_step = (state->red.u - state->green.u) / (state->lifetime.s - 0xF);
            color = state->green.u + color_step;
            state->green.u = color;
            primitive->color.c.g = color;

            color_step = (state->red.u - state->blue.u) / (state->lifetime.s - 0xF);
            color = state->blue.u + color_step;
            state->blue.u = color;
            primitive->color.c.b = color;
        } else if (state->lifetime.s >= 8) {
            scaled_color = state->red.u * (state->lifetime.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->color.c.r = scaled_color >> 3;

            scaled_color = state->green.u * (state->lifetime.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->color.c.g = scaled_color >> 3;

            scaled_color = state->blue.u * (state->lifetime.s - 8);
            primitive->color.c.b = scaled_color / 8;
        } else {
            state->lifetime.s = 0;
        }
    }

    frames_left = state->lifetime.u - 1;
    state->lifetime.s = frames_left;
    if ((frames_left << 16) <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
