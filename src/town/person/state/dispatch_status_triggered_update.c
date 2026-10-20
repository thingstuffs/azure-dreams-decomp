#include "common.h"
#include "shared/sprite_frame_state.h"

/* extern */

   /* arg2 in dispatch_status_triggered_update */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Calls the handler when either monitored status flag is set. */
void dispatch_status_triggered_update(s32 handler_arg, s32 context, SpriteFlagsView *status) {
    if (status->unk_14 & 0x6000) {
        apply_object_setup_and_update(handler_arg, context, status);
    }
}
