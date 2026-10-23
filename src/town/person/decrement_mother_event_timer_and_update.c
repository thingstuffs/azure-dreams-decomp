#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void decrement_mother_event_timer_and_update(Rec_func_80094268_arg0 *object, s32 callback_arg_1, s32 callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
