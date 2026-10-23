#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

typedef struct CallbackOwner {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;

extern u8 actor_action_resume_address[];

/*
 * Resumes actor action handling after thrown travel completes and the floor-trap check returns
 * positive.
 */
void install_actor_action_handler_after_thrown_travel(CallbackOwner *owner, ObjectPosition *position, void *tile, ActorRecord *actor) {
    void *state = owner;
    if (update_thrown_actor_travel(state, position, tile, actor) && (s16) check_actor_floor_trap(tile, actor) > 0) {
        owner->callback = actor_action_resume_address;
    }
}
