#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800980B4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800980B4_0;   /* arg0 in func_800980B4 */


M2C_UNK func_80098928(S_800980B4_0 *, s32, s32);
/* Decrement the countdown, then call func_80098928 and set unk_10 to 0x400 at zero. */
void func_800980B4(S_800980B4_0 *state, s32 value, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_80098928(state, value, mode);
        state->unk_10 = 0x400;
    }
}
