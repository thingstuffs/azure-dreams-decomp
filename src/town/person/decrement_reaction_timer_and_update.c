#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the object countdown and call apply_object_setup_and_update when it expires. */
void decrement_reaction_timer_and_update(Rec_func_80094268_arg0 *object, s32 param_1, s32 param_2) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, param_1, param_2);
    }
}
