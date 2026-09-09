#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_8009803C_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8009803C_0;   /* arg0 in func_8009803C */


M2C_UNK func_80098928(S_8009803C_0 *, s32, s32);
/* Decrement the countdown and call func_80098928 when it reaches zero. */
void func_8009803C(S_8009803C_0 *state, s32 value, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_80098928(state, value, mode);
    }
}
