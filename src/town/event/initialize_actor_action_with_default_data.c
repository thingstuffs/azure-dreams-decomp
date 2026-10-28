#include "common.h"
#include "town/event/object_setup.h"
#include "m2c_compat.h"

extern M2C_UNK D_800F8A58;

/* Initialize the actor's action using D_800F8A58. */
void initialize_actor_action_with_default_data(void *actor, void *action_id, struct SpriteFrameState *action_state) {
    initialize_actor_action_with_defaults(actor, action_id, action_state, &D_800F8A58);
}
