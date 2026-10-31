#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Returns without reading or changing state. */
void no_op_actor_dispatch(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *render, ActorRecord *context)
{
}
