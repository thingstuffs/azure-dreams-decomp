#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

/* extern */
                /* extern */
extern u8 actor_default_action_address;

/* Select D_800D4494 after the countdown completes and the actor check succeeds. */
void install_actor_action_handler(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if ((update_linked_actor_motion(body, position, sprite, actor) != 0) && ((check_actor_floor_trap(sprite, actor) << 0x10) > 0)) {
        body->unk_8C.address = &actor_default_action_address;
    }
}
