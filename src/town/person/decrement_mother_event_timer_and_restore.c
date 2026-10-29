#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown, then restore unk_72 from unk_6E and call apply_object_setup_and_update when it expires. */
void decrement_mother_event_timer_and_restore(Rec_func_80094268_arg0 *object, void *callback_arg_1, void *callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        object->unk_72.as_u16 = (u16) object->unk_6E;
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
