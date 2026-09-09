#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_80098078_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80098078_0;   /* arg0 in func_80098078 */


M2C_UNK func_80098988(S_80098078_0 *, s32);
/* Decrement the countdown and call func_80098988 when it reaches zero. */
void func_80098078(S_80098078_0 *state, s32 value) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_80098988(state, value);
    }
}
