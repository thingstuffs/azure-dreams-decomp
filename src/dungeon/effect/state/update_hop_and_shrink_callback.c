#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/effect/state.h"

/* Forward the motion, sprite and render state to the hop update. */
s32 update_hop_and_shrink_callback(ActorRecord *state, ObjectPosition *context, SpriteFrameState *data, ActorRecord *render) {
    return update_actor_hop_and_shrink(state, context, data, render);
}
