#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_80098078_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80098078_0;   /* arg0 in townTickCountdownAndInitializeTarget */


void townInitializeTargetAndHandlerTable(S_80098078_0 *, s32);
/* Decrement the countdown and call townInitializeTargetAndHandlerTable when it reaches zero. */
void townTickCountdownAndInitializeTarget(S_80098078_0 *state, s32 value) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        townInitializeTargetAndHandlerTable(state, value);
    }
}
