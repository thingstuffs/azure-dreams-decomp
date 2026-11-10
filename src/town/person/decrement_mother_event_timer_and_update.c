#include "common.h"
#include "shared/town_object.h"

/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void decrement_mother_event_timer_and_update(TownObjectRecord *object, void *callback_arg_1, void *callback_arg_2) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
