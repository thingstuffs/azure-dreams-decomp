#include "common.h"
#include "shared/sprite_frame_state.h"

void install_object_handler_and_clear_slot_flag(void *object);

   /* arg2 in dispatch_status_triggered_handler */

/* Calls the object handler when either monitored status flag is set. */
void dispatch_status_triggered_handler(s32 object, s32 unused, SpriteFlagsView *status) {
    if (status->flags & 0x6000) {
        install_object_handler_and_clear_slot_flag(object);
    }
}
