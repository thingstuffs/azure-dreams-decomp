#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/actor/motion.h"
#include "dungeon/effect/state.h"

/* extern */

/* Set the state pointer to dispatch_target_action when update_linked_actor_motion succeeds. */
void set_effect_state_pointer_on_success(ActorRecord *state, ObjectPosition *context, SpriteFrameState *data, ActorRecord *extra_data) {
    if (update_linked_actor_motion(state, context, data, extra_data) != 0) {
        state->unk_8C.address = &dispatch_target_action;
    }
}
