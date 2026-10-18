#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void advance_dispatch_state_to_two(void);                            /* extern */

/* Forward both inputs to advance_dispatch_state_to_two. */
void ignore_inputs_and_run_event_reset(s32 first_input, s32 second_input) {
    advance_dispatch_state_to_two();
}
