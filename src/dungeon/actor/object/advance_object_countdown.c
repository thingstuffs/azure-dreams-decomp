#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 apply_object_setup_and_update(void *, s32, s32);    /* extern */

/* Decrements an object's countdown and invokes both handlers when it expires. */
void advance_object_countdown_and_invoke_handlers(Rec_func_80094268_arg0 *object, s32 handlerContext, s32 handlerData) {
    u16 remainingCount;

    remainingCount = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remainingCount;
    if ((remainingCount << 0x10) <= 0) {
        set_record_data_pointer(object);
        apply_object_setup_and_update(object, handlerContext, handlerData);
    }
}
