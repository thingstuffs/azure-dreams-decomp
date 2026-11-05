#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void apply_setup_on_timeout_variant_2();
extern s32 D_800D5944[];


/* Switch the actor state and callback when the countdown expires, then reset it to five ticks. */
void switch_actor_state(TownObjectRecord *actor, s32 unused, void *state_context) {
    u16 ticks_left;

    ticks_left = actor->timer - 1;
    actor->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_object_entries((actor), state_context, D_800D5944);
        actor->handler = &apply_setup_on_timeout_variant_2;
        actor->timer = 5U;
    }
}
