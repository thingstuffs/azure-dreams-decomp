#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "town/event/motion.h"
#include "town/event.h"


/*
 * Sets the state byte at offset 0x15 and assigns actor_surface_callback_address to the object data
 * pointer.
 */
void set_actor_motion_state(TownObjectRecord *object, Rec_D_800CFCB4 *state, struct ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    state->unk_15 = 1;
    object->state_callback.as_pm = update_actor_surface_motion;
}
