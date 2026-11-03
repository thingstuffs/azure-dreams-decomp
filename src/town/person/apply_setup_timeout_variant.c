#include "common.h"
#include "shared/town_object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void apply_setup_on_timeout_variant_1(TownObjectRecord *object, ObjectPosition *position, void *callback_arg_2) {
    u16 countdown;

    countdown = object->timer.as_u16 - 1;
    object->timer.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, position, callback_arg_2);
    }
}
