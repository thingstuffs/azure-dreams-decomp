#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 apply_object_setup_and_update(void *);                            /* extern */


/* Decrement the object counter and call its handler when it reaches zero. */
void apply_setup_on_timeout_variant_3(Rec_func_80094268_arg0 *object) {
    u16 remaining_count;

    remaining_count = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        apply_object_setup_and_update(object);
    }
}
