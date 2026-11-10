#include "common.h"
#include "shared/town_object.h"

/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the object countdown and call apply_object_setup_and_update when it expires. */
void decrement_reaction_timer_and_update(TownObjectRecord *object, void *param_1, void *param_2) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, param_1, param_2);
    }
}
