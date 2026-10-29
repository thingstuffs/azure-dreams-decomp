#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"

/* extern */

typedef struct S_800980B4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800980B4_0;   /* arg0 in tick_countdown_and_reset_value */


void initialize_record_with_handler_table(S_800980B4_0 *, s32, s32);
/* Decrement the countdown, then call initialize_record_with_handler_table and set unk_10 to 0x400 at zero. */
void tick_countdown_and_reset_value(S_800980B4_0 *state, s32 value, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_table(state, value, mode);
        state->unk_10 = 0x400;
    }
}
