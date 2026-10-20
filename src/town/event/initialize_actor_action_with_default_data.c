#include "common.h"
#include "m2c_compat.h"

void initialize_actor_action_with_defaults();                   /* extern */
extern M2C_UNK D_800F8A58;

/* Initialize the actor's action using D_800F8A58. */
void initialize_actor_action_with_default_data(s32 actor, s32 action_id, s32 action_state) {
    initialize_actor_action_with_defaults(actor, action_id, action_state, &D_800F8A58);
}
