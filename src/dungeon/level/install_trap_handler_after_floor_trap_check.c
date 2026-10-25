#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/state.h"
#include "dungeon/level.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;

/*
 * Runs resolve_actor_floor_trap_once and installs update_actor_facing_animation when it returns
 * positive.
 */
void install_trap_handler_after_floor_trap_check(void *owner_in, s32 context, void *source, void *target) {
    CallbackOwner *owner = owner_in;
    if (resolve_actor_floor_trap_once(owner_in, context, source, target) > 0) {
        owner->callback = update_actor_facing_animation;
    }
}
