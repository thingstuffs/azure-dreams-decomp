
#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/hikewne.h"

/* extern */



/* Call update_actor_hop_and_shrink and clear the state field at offset 0xA2. */
void update_hikewne_hop_and_shrink(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    update_actor_hop_and_shrink(body, position, sprite, actor);
    body->unk_A0.parts.high = 0;
}
