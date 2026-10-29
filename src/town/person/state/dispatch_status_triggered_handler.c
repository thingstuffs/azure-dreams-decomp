#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/state.h"

   /* arg2 in dispatch_status_triggered_handler */

/* Calls the object handler when either monitored status flag is set. */
void dispatch_status_triggered_handler(s32 object, s32 unused, SpriteFlagsView *status) {
    if (status->flags & 0x6000) {
        install_object_handler_and_clear_slot_flag(object);
    }
}
