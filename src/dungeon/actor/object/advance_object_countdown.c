#include "common.h"
#include "shared/town_object.h"
#include "town/person.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 apply_object_setup_and_update(void *, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */    /* extern */

/* Decrements an object's countdown and invokes both handlers when it expires. */
void advance_object_countdown_and_invoke_handlers(TownObjectRecord *object, s32 handlerContext, s32 handlerData) {
    u16 remainingCount;

    remainingCount = object->timer.as_u16 - 1;
    object->timer.as_u16 = remainingCount;
    if ((remainingCount << 0x10) <= 0) {
        set_record_data_pointer(object);
        apply_object_setup_and_update(object, handlerContext, handlerData);
    }
}
