#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 propagate_actor_action_flag(void);
extern u8 D_800D8C64[];

void install_trap_handler_after_action_flag_propagation(CallbackOwner *owner) {
    if (propagate_actor_action_flag() > 0) {
        owner->callback = D_800D8C64;
    }
}
