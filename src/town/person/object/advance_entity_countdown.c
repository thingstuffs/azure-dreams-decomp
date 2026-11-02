#include "common.h"
#include "shared/town_object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

#include "town/person/object_setup.h"
#include "town/person/object.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void advance_entity_countdown(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->timer.as_u16 - 1;
    object->timer.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}
