#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/effect/state.h"

/* Forward the motion, sprite and render state to the hop update. */
s32 forward_actor_effect_state(void *state, void *context, SpriteFrameState *data, void *render) {
    return update_actor_hop_and_shrink(state, context, data, render);
}
