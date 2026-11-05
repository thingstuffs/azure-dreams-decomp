#include "common.h"
#include "shared/town_object.h"
#include "dungeon/actor.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 apply_object_setup_and_update(void *); /* Unprototyped: retail call passes a different argument count */                            /* extern */


/* Decrement the object counter and call its handler when it reaches zero. */
void apply_setup_on_timeout_variant_3(TownObjectRecord *object) {
    u16 remaining_count;

    remaining_count = object->timer - 1;
    object->timer = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        apply_object_setup_and_update(object);
    }
}
