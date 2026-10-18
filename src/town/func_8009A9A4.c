#include "common.h"

#include "records/Rec_func_80094268_arg0.h"
#include "shared/types3a_types.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

   /* arg0 in tick_countdown_and_initialize_handler */


void initialize_record_with_handler_and_count(Rec_func_80094268_arg0 *record, s32 setup_value, void *ptr2);
/* Decrement the countdown and call initialize_record_with_handler_and_count when it reaches zero. */
void tick_countdown_and_initialize_handler(UnsignedCountdownView *state, s32 context, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_and_count(state, context, mode);
    }
}
