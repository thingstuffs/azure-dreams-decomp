#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

   /* arg0 in tick_countdown_and_initialize_target */


void initialize_target_and_handler_table(UnsignedCountdownView *, s32);
/* Decrement the countdown and call initialize_target_and_handler_table when it reaches zero. */
void tick_countdown_and_initialize_target(UnsignedCountdownView *state, s32 value) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_target_and_handler_table(state, value);
    }
}
