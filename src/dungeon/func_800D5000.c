#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_spinning_actor_fall(void);
extern u8 D_800D8C64[];

void install_trap_handler_after_spinning_fall(CallbackOwner *owner) {
    if (update_spinning_actor_fall() != 0) {
        owner->callback = D_800D8C64;
    }
}
