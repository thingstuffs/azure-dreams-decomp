#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

   /* arg0 in tick_countdown_and_initialize_record */


void initialize_record_with_handler_table(UnsignedCountdownView *, s32, s32);
/* Decrement the countdown and call initialize_record_with_handler_table when it reaches zero. */
void tick_countdown_and_initialize_record(UnsignedCountdownView *state, s32 value, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_table(state, value, mode);
    }
}
