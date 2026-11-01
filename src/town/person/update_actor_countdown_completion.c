#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
void func_800CB73C(TownObjectRecord *);                            /* extern */

/* Decrement the actor's countdown and run its expiration actions when it expires. */
void update_actor_countdown_completion(TownObjectRecord *actor, void *update_context, void *setup_context) {
    u16 countdown;

    countdown = actor->timer.as_u16 - 1;
    actor->timer.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB73C(actor);
        allocate_variant_object(actor->variant.as_s8, actor->target_x, actor->target_y);
        apply_object_setup_and_update(actor, update_context, setup_context);
    }
}
