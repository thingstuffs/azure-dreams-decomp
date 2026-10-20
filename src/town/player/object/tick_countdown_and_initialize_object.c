#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

/* extern */

   /* arg0 in tick_countdown_and_initialize_object */


void initialize_object_transform_and_handler(UnsignedCountdownView *, void *, s32);
/* Decrement the countdown and call initialize_object_transform_and_handler when it reaches zero. */
void tick_countdown_and_initialize_object(UnsignedCountdownView *state, void *context, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_transform_and_handler(state, context, mode);
    }
}
