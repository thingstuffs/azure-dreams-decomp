#include "common.h"
#include "dungeon/actor.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_actor_transform_from_parent(void);

extern u8 actor_action_resume_address[];

/*
 * Resumes actor action handling after the parent transform update succeeds and the floor-trap
 * check returns positive.
 */
void install_actor_action_handler_after_floor_trap_check(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (update_actor_transform_from_parent() && (s16) check_actor_floor_trap(first, second) > 0) {
        owner->callback = actor_action_resume_address;
    }
}
