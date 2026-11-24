#include "dungeon/monster/weadog.h"
#include "dungeon/monster/blume.h"
#include "dungeon/actor/effect.h"

/* Resume the action dispatcher when the actor's fade-in completes. */
void finish_weadog_fade_in(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *context) {
    if (update_actor_fade_in(actor, position, sprite)) {
        actor->unk_8C.handler = dispatch_blume_actions;
    }
}
