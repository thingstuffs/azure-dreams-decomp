#include "common.h"
#include "town/event/object_setup.h"
#include "m2c_compat.h"

extern M2C_UNK D_800F8A4C;

/* Initialize the object's action state using D_800F8A4C. */
void initialize_object_action_with_default_data(void *object, void *action, struct SpriteFrameState *state) {
    initialize_actor_action_with_defaults(object, action, state, &D_800F8A4C);
}
