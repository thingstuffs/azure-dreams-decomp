#include "common.h"
#include "m2c_compat.h"


typedef struct S_800A7950_0 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A7950_0;   /* arg2 in func_800A7950 */

typedef struct S_800A7950_1 {
    u8 pad_00[0x6C];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800A7950_1;   /* arg0 in func_800A7950 */


extern void func_800A79C8(S_800A7950_1 *, void *, S_800A7950_0 *);
/* Update scale from elapsed ticks and advance when the countdown expires. */
void func_800A7950(S_800A7950_1 *state, void *context, S_800A7950_0 *scale) {
    s16 ticks_left;

    scale->unk_1C = (s16) (((state->unk_90 - state->unk_6C) * 8) + 0x1000);
    scale->unk_1E = (s16) (0x1000 - ((state->unk_90 - state->unk_6C) * 2));
    ticks_left = (u16) state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if (ticks_left < 0) {
        func_800A79C8(state, context, scale);
    }
}
