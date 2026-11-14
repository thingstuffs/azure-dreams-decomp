#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/event.h"


/* Forward both inputs to advance_event_dispatch_state. */
void advance_dispatch_state_on_request(void *first_input, s32 second_input) {
    advance_event_dispatch_state();
}
