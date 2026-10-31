#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Forward both inputs to advance_dispatch_state_to_two. */
void ignore_inputs_and_run_event_reset(void *first_input, s32 second_input) {
    advance_dispatch_state_to_two();
}
