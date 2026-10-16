#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 dungeonResolveActorFloorTrapOnce(void);
extern u8 D_800D8C64[];

void func_800DA7D0(CallbackOwner *owner) {
    if (dungeonResolveActorFloorTrapOnce() > 0) {
        owner->callback = D_800D8C64;
    }
}
