#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the object countdown and call apply_object_setup_and_update when it expires. */
void decrement_reaction_timer_and_update(Rec_func_80094268_arg0 *object, void *param_1, void *param_2) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, param_1, param_2);
    }
}
