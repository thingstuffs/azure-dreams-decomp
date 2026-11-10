#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"

/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the object countdown and call initialize_reaction_movement when it expires. */
void decrement_reaction_timer_and_reinitialize(TownObjectRecord *object, void *context, void *param) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_reaction_movement(object, context, param);
    }
}
