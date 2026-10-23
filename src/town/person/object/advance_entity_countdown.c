#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void advance_entity_countdown(Rec_func_80094268_arg0 *object, s32 context, s32 update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}
