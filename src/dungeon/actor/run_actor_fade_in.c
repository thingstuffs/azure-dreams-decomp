#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_actor_fade_in(void);
extern u8 actor_action_resume_address[];

void run_actor_fade_in(CallbackOwner *owner) {
    if (update_actor_fade_in() != 0) {
        owner->callback = actor_action_resume_address;
    }
}
