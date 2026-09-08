#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
typedef struct S_800A70EC_0 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x18];
    union { u16 u; s16 s; } unk_6C;   /* accessed as both */
} S_800A70EC_0;   /* arg0 in func_800A70EC */

typedef struct S_800A70EC_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800A70EC_1;   /* arg3 in func_800A70EC */

/* extern */

/* Update the countdown-driven scale effect and clear it when the countdown expires. */
void func_800A70EC(S_800A70EC_0 *state, s32 unused_1, s32 unused_2, S_800A70EC_1 *scale) {
    s32 z_wave;
    s32 x_wave;
    s32 y_wave;
    s32 z_offset;
    u16 ticks_left;

    ticks_left = state->unk_6C.u - 1;
    state->unk_6C.u = ticks_left;
    if ((s16) ticks_left <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        state->unk_50 = 0;
        return;
    }
    x_wave = func_800644B8((s16) ticks_left * 0xCC);
    if (x_wave < 0) {
        x_wave += 7;
    }
    scale->unk_1C = (s16) ((x_wave >> 3) + 0x1000);
    y_wave = func_800644B8(state->unk_6C.s * 0xCC);
    if (y_wave < 0) {
        y_wave += 7;
    }
    scale->unk_1E = (s16) ((y_wave >> 3) + 0x1000);
    z_wave = func_800644B8(state->unk_6C.s * 0xCC);
    z_offset = z_wave >> 3;
    if (z_wave < 0) {
        z_offset = (s32) (z_wave + 7) >> 3;
    }
    scale->unk_20 = (s16) (0x1000 - z_offset);
}
