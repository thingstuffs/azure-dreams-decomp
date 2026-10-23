#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 propagate_actor_action_flag(void);
extern u8 actor_action_resume_address[];

/* Installs actor_action_resume_address when action-flag propagation returns positive. */
void install_trap_handler_after_action_flag_propagation(CallbackOwner *owner) {
    if (propagate_actor_action_flag() > 0) {
        owner->callback = actor_action_resume_address;
    }
}
