#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80097EC0_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80097EC0_0;   /* arg0 in townTickCountdownAndInitializeObject */


void townInitializeObjectTransformAndHandler(S_80097EC0_0 *, void *, s32);
/* Decrement the countdown and call townInitializeObjectTransformAndHandler when it reaches zero. */
void townTickCountdownAndInitializeObject(S_80097EC0_0 *state, void *context, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        townInitializeObjectTransformAndHandler(state, context, mode);
    }
}
