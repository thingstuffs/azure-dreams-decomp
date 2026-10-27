#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/state.h"

/* Tests flag 0x08000000 and propagates flag 0x40000 when it is set. */
s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 flags = actor->flags1C;

    if (flags & ACTOR_GROUNDED) {
        if (actor->flags14 & 0x40000) {
            actor->flags1C = flags | 0x40000;
        }
        return 1;
    }
    return 0;
}
