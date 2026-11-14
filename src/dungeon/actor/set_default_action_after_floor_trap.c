#include "common.h"

#include "dungeon/actor/state.h"
#include "dungeon/actor.h"
extern u8 actor_default_action_address;

/* Sets the object data pointer when the status check is positive. */
void set_default_action_after_floor_trap(ActorRecord *body, ObjectPosition *position, SpriteFrameState *source, ActorRecord *actor) {
    if (resolve_actor_floor_trap_once(body, position, source, actor) > 0) {
        body->unk_8C.address = &actor_default_action_address;
    }
}
