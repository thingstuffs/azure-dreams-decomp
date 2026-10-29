#include "dungeon/actor/animation.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Reset the entity to state 0x3A and clear its context's 0x20 flag. */
void finish_paralyzed_actor_action(ActorRecord *entity, void *unused_1, SpriteFrameState *unused_2, ActorRecord *context) {
    entity->action_id.s = 0x3A;
    entity->action_phase.s = 0;
    entity->unk_8C.address = 0;
    entity->action_timer.s = 0;
    context->flags1C = (s32) (context->flags1C & ~ACTOR_PARALYZED);
}
