#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void apply_setup_on_timeout_variant_4(Rec_func_80094268_arg0 *object, void *context, void *update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}
