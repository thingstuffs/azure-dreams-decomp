#include "common.h"
#include "dungeon/actor/effect.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern u8 actor_action_resume_address[];

/* Runs the actor fade-in step and installs actor_action_resume_address when it completes. */
void run_actor_fade_in(void *owner_in, s32 context, void *effect) {
    CallbackOwner *owner = owner_in;
    if (update_actor_fade_in(owner_in, context, effect) != 0) {
        owner->callback = actor_action_resume_address;
    }
}
