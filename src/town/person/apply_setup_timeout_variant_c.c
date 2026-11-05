#include "common.h"
#include "shared/town_object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void apply_setup_on_timeout_variant_3(TownObjectRecord *object, void *context, void *update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->timer - 1;
    object->timer = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}
