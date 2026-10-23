#include "common.h"
#include "dungeon/actor.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_thrown_actor_travel(void);

extern u8 actor_action_resume_address[];

void install_actor_action_handler_after_thrown_travel(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (update_thrown_actor_travel() && (s16) check_actor_floor_trap(first, second) > 0) {
        owner->callback = actor_action_resume_address;
    }
}
