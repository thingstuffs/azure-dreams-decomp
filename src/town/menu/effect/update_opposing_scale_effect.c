#include "common.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"

/* extern */
typedef struct S_800A79F0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800A79F0_0;   /* arg0 in update_opposing_scale_effect */

typedef struct S_800A79F0_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A79F0_1;   /* arg2 in update_opposing_scale_effect */

/* extern */


void initialize_randomized_scale_timer(S_800A79F0_0 *);
/* Update opposing scale offsets until the countdown ends, then restore unit scale. */
void update_opposing_scale_effect(S_800A79F0_0 *state, s32 unused_1, S_800A79F0_1 *scale, s32 unused_3) {
    u16 ticks_left;
    s32 scale_wave;
    s32 scale_offset;
    s32 rounded_wave;

    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((s16) ticks_left <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        initialize_randomized_scale_timer(state);
        return;
    }
    scale_wave = rsin((s16) ticks_left * 0xBA);
    scale_offset = scale_wave >> 2;
    if (scale_wave < 0) {
        scale_offset = (s32) (scale_wave + 3) >> 2;
    }
    scale->unk_1C = (s16) (0x1000 - scale_offset);
    rounded_wave = rsin((s16) state->unk_6C * 0xBA);
    scale->unk_1E = (s16) ((rounded_wave / 4) + 0x1000);
}
