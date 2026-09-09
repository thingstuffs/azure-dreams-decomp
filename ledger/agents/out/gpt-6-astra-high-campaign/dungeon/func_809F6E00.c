#include "common.h"

typedef struct S_80174600_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80174600_0;   /* arg2 in func_80174600 */

typedef struct S_80174600_1 {
    u8 pad_00[0x1A];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
} S_80174600_1;   /* p in func_80174600 */



extern s32 D_800814A0;

/* Animate primitive colors and mark the effect finished when its timer expires. */
void func_80174600(void *effect_state, s32 unused, void *primitive)
{
    u8 *state = effect_state;
    s16 frames_left;
    s32 scaled_color;
    s32 color_step;
    u8 color;

    ((S_80174600_0 *)primitive)->unk_1A += 0x320;

    if (((S_80174600_1 *)state)->unk_1A.s >= 0x33) {
        ((S_80174600_0 *)primitive)->unk_0C = (state[0] * (0x41 - ((S_80174600_1 *)state)->unk_1A.s)) / 14;
        ((S_80174600_0 *)primitive)->unk_0D = (state[1] * (0x41 - ((S_80174600_1 *)state)->unk_1A.s)) / 14;
        ((S_80174600_0 *)primitive)->unk_0E = (state[2] * (0x41 - ((S_80174600_1 *)state)->unk_1A.s)) / 14;
    } else if (((S_80174600_1 *)state)->unk_1A.s < 0x1A) {
        if (((S_80174600_1 *)state)->unk_1A.s >= 0x10) {
            color_step = (state[0] - state[1]) / (((S_80174600_1 *)state)->unk_1A.s - 0xF);
            color = state[1] + color_step;
            state[1] = color;
            ((S_80174600_0 *)primitive)->unk_0D = color;

            color_step = (state[0] - state[2]) / (((S_80174600_1 *)state)->unk_1A.s - 0xF);
            color = state[2] + color_step;
            state[2] = color;
            ((S_80174600_0 *)primitive)->unk_0E = color;
        } else if (((S_80174600_1 *)state)->unk_1A.s >= 8) {
            scaled_color = state[0] * (((S_80174600_1 *)state)->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            ((S_80174600_0 *)primitive)->unk_0C = scaled_color >> 3;

            scaled_color = state[1] * (((S_80174600_1 *)state)->unk_1A.s - 8);
            if (scaled_color < 0) {
                scaled_color += 7;
            }
            ((S_80174600_0 *)primitive)->unk_0D = scaled_color >> 3;

            scaled_color = state[2] * (((S_80174600_1 *)state)->unk_1A.s - 8);
            ((S_80174600_0 *)primitive)->unk_0E = scaled_color / 8;
        } else {
            ((S_80174600_1 *)state)->unk_1A.s = 0;
        }
    }

    frames_left = ((S_80174600_1 *)state)->unk_1A.u - 1;
    ((S_80174600_1 *)state)->unk_1A.s = frames_left;
    if ((frames_left << 16) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
