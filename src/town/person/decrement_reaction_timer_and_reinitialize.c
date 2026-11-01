#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the object countdown and call initialize_reaction_movement when it expires. */
void decrement_reaction_timer_and_reinitialize(TownObjectRecord *object, void *context, void *param) {
    u16 countdown;

    countdown = object->timer.as_u16 - 1;
    object->timer.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_reaction_movement(object, context, param);
    }
}
