#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_actor_fade_in(void);
extern u8 D_800D8C64[];

void func_800DA798(CallbackOwner *owner) {
    if (update_actor_fade_in() != 0) {
        owner->callback = D_800D8C64;
    }
}
