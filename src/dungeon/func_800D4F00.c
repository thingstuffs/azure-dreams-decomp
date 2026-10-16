#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 func_800AC82C(void);
extern s16 dungeonCheckActorFloorTrap(s32, s32);
extern u8 D_800D8C64[];

void func_800DA660(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (func_800AC82C() && dungeonCheckActorFloorTrap(first, second) > 0) {
        owner->callback = D_800D8C64;
    }
}
