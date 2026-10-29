#include "common.h"
#include "town/person/state_updates.h"
#include "shared/sprite_frame_state.h"

/* extern */

   /* arg2 in dispatch_status_triggered_update */
#include "town/person/object_setup.h"
#include "town/person/state.h"
#include "town/person/object.h"
/* Calls the handler when either monitored status flag is set. */
void dispatch_status_triggered_update(void *handler_arg, void *context, SpriteFlagsView *status) {
    if (status->flags & 0x6000) {
        apply_object_setup_and_update(handler_arg, context, status);
    }
}
