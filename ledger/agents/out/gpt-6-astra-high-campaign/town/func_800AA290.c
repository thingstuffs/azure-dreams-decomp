#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
/* extern */
typedef struct S_800A79F0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800A79F0_0;   /* arg0 in func_800A79F0 */

typedef struct S_800A79F0_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A79F0_1;   /* arg2 in func_800A79F0 */

/* extern */


M2C_UNK func_800A790C(S_800A79F0_0 *, s32, S_800A79F0_1 *, s32);
/* Update opposing scale offsets until the countdown ends, then restore unit scale. */
void func_800A79F0(S_800A79F0_0 *state, s32 finish_arg1, S_800A79F0_1 *scale, s32 finish_arg3) {
    u16 ticks_left;
    s32 scale_wave;
    s32 scale_offset;
    s32 rounded_wave;

    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((s16) ticks_left <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        func_800A790C(state, finish_arg1, scale, finish_arg3);
        return;
    }
    scale_wave = func_800644B8((s16) ticks_left * 0xBA);
    scale_offset = scale_wave >> 2;
    if (scale_wave < 0) {
        scale_offset = (s32) (scale_wave + 3) >> 2;
    }
    scale->unk_1C = (s16) (0x1000 - scale_offset);
    rounded_wave = func_800644B8((s16) state->unk_6C * 0xBA);
    if (rounded_wave < 0) {
        rounded_wave += 3;
    }
    scale->unk_1E = (s16) ((rounded_wave >> 2) + 0x1000);
}
