#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 resolve_actor_floor_trap_once(void);
extern u8 actor_action_resume_address[];

/*
 * Runs resolve_actor_floor_trap_once and installs actor_action_resume_address when it returns
 * positive.
 */
void install_trap_handler_after_floor_trap_check(CallbackOwner *owner) {
    if (resolve_actor_floor_trap_once() > 0) {
        owner->callback = actor_action_resume_address;
    }
}
