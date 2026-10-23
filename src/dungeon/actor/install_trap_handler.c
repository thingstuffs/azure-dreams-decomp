#include "common.h"
#include "dungeon/actor/state.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern u8 actor_action_resume_address[];

/* Installs actor_action_resume_address when action-flag propagation returns positive. */
void install_trap_handler_after_action_flag_propagation(void *owner_in, s32 context, s32 sprite, s32 *record) {
    CallbackOwner *owner = owner_in;
    if (propagate_actor_action_flag(owner_in, context, sprite, record) > 0) {
        owner->callback = actor_action_resume_address;
    }
}
