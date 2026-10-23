#include "common.h"
#include "dungeon/actor.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_thrown_actor_travel(void);

extern u8 D_800D8C64[];

void install_actor_action_handler_after_thrown_travel(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (update_thrown_actor_travel() && (s16) check_actor_floor_trap(first, second) > 0) {
        owner->callback = D_800D8C64;
    }
}
