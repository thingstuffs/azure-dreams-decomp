#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "town/event/motion.h"

extern void actor_surface_callback_address(void *actor, void *subject, void *motion, void *context);
/*
 * Sets the state byte at offset 0x15 and assigns actor_surface_callback_address to the object data
 * pointer.
 */
void set_actor_motion_state(TownObjectRecord *object, Rec_D_800CFCB4 *state) {
    state->unk_15 = 1;
    object->unk_50.as_pm = &actor_surface_callback_address;
}
