#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_8009F148(); /* extern */

typedef struct S_8009F374_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009F374_0;   /* arg2 in func_8009F374 */

typedef struct S_8009F374_1 {
    u8 pad_00[0x6C];
    s16 unk_6C;
    u8 pad_6E[0x32];
    s32 unk_A0;
} S_8009F374_1;   /* arg0 in func_8009F374 */

typedef struct S_8009F374_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009F374_2;   /* arg3 in func_8009F374 */

/* Jitter the position and pulse the scale until the countdown expires. */
void func_8009F374(S_8009F374_1 *state, M2C_UNK context, S_8009F374_0 *position, S_8009F374_2 *scale) {
    s16 ticks_left;
    s32 scale_x_wave;
    s32 scale_y_wave;

    position->unk_08 = (s32) (state->unk_A0 + (((func_800374F4(0x10) & 0xFFFF) - 8) << 0x10));
    scale_x_wave = func_800644B8(state->unk_6C * 0x199);
    if (scale_x_wave < 0) {
        scale_x_wave += 3;
    }
    scale->unk_1C = (s16) ((scale_x_wave >> 2) + 0x1000);
    scale_y_wave = func_800644B8(state->unk_6C * 0x199);
    if (scale_y_wave < 0) {
        scale_y_wave += 3;
    }
    scale->unk_1E = (s16) (0x1000 - (scale_y_wave >> 2));
    ticks_left = (u16) state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        func_8009F148(state, context, position, scale);
    }
}
