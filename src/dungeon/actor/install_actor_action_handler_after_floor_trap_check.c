#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

typedef struct CallbackOwner {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;

/*
 * Resumes actor action handling after the parent transform update succeeds and the floor-trap
 * check returns positive.
 */
void install_actor_action_handler_after_floor_trap_check(CallbackOwner *owner, ObjectPosition *position, void *tile, ActorRecord *actor) {
    void *state = owner;
    if (update_actor_transform_from_parent(state, position, tile, actor) && (s16) check_actor_floor_trap(tile, actor) > 0) {
        owner->callback = update_actor_facing_animation;
    }
}
