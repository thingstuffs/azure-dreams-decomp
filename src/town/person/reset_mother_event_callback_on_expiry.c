#include "common.h"

extern s32 select_object_setup_path(s32, s32, s32, s32);
extern void initialize_mother_event_with_timer_16(s32, s32, s32);
extern s32 D_80113220[];

/* Reset the object callback when the shared countdown expires after a zero check result. */
void reset_mother_event_callback_on_expiry(s32 object, s32 motion, s32 init_data, s32 check_arg) {
    if (select_object_setup_path(object, motion, init_data, check_arg) == 0) {
        if (--D_80113220[0] <= 0) {
            initialize_mother_event_with_timer_16(object, motion, init_data);
        }
    }
}
