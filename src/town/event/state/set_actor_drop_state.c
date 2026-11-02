#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/event/state.h"
#include "town/event/motion.h"
/* Set the state flag and assign the object's data pointer. */
void set_actor_drop_state(TownObjectRecord *object, Rec_D_800CFCB4 *state) {
    state->unk_15 = 1;
    object->unk_50.as_pm = &update_motion_and_handle_terrain_contact;
}
