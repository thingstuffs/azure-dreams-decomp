#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 resolve_actor_floor_trap_once(void);
extern u8 D_800D8C64[];

void install_trap_handler_after_floor_trap_check(CallbackOwner *owner) {
    if (resolve_actor_floor_trap_once() > 0) {
        owner->callback = D_800D8C64;
    }
}
