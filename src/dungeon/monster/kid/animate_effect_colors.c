#include "shared/object_node.h"
#include "dungeon/monster/kid.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80174600_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80174600_0;   /* arg2 in animate_effect_colors */

/* Animate primitive colors and mark the effect finished when its timer expires. */
void animate_effect_colors(RandomlyRotatedOffsetEffectBody *effect_state, ObjectPosition *unused, void *primitive_arg)
{
    RandomlyRotatedOffsetEffectBody *state = effect_state;
    s16 frames_left;
    s32 scaled_color;
    s32 color_step;
    u8 color;
    S_80174600_0 *primitive = primitive_arg;

    primitive->unk_1A += 0x320;

    if (state->unk_1A.s >= 0x33) {
        primitive->unk_0C = (state->unk_00.u * (0x41 - state->unk_1A.s)) / 14;
        primitive->unk_0D = (state->unk_01.u * (0x41 - state->unk_1A.s)) / 14;
        primitive->unk_0E = (state->unk_02.u * (0x41 - state->unk_1A.s)) / 14;
    } else if (state->unk_1A.s < 0x1A) {
        if (state->unk_1A.s >= 0x10) {
            color_step = (state->unk_00.u - state->unk_01.u) / (state->unk_1A.s - 0xF);
            color = state->unk_01.u + color_step;
            state->unk_01.u = color;
            primitive->unk_0D = color;

            color_step = (state->unk_00.u - state->unk_02.u) / (state->unk_1A.s - 0xF);
            color = state->unk_02.u + color_step;
            state->unk_02.u = color;
            primitive->unk_0E = color;
        } else if (state->unk_1A.s >= 8) {
            scaled_color = state->unk_00.u * (state->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->unk_0C = scaled_color >> 3;

            scaled_color = state->unk_01.u * (state->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            primitive->unk_0D = scaled_color >> 3;

            scaled_color = state->unk_02.u * (state->unk_1A.s - 8);
            primitive->unk_0E = scaled_color / 8;
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
