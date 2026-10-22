
struct SpriteFrameState;
#include "common.h"
#include "m2c_compat.h"

s32 update_actor_hop_and_shrink(void *, void *,struct SpriteFrameState *);                            /* extern */

/* Forward the state, context, and data to update_actor_hop_and_shrink. */
void forward_actor_effect_state(void *state, void *context, void *data) {
    update_actor_hop_and_shrink(state, context, data);
}
