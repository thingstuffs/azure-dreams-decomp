#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */

/*
 * Updates linked actor motion and restores facing animation once motion succeeds and the
 * floor-trap check returns positive.
 */
void update_linked_motion_and_floor_trap(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if ((update_linked_actor_motion(body, position, sprite, actor) != 0) && ((check_actor_floor_trap(sprite, actor) << 0x10) > 0)) {
        body->unk_8C.address = &update_actor_facing_animation;
    }
}
