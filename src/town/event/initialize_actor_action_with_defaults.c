#include "common.h"
#include "town/event/object_setup.h"

extern s32 D_800D0678[];

/* Initialize the actor's action with shared state data and D_800D0678. */
void initialize_actor_action_with_defaults(void *actor, void *action_id, struct SpriteFrameState *action_state, void *state_data) {
    select_object_state_by_mode(actor, action_id, action_state, state_data, state_data, D_800D0678);
}
