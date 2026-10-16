/* Relink of matched dungeon/func_800D4F00; every changed retail word is a paired relocation. */
#define D_800D8C64 D_8016B778
#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 func_800AC82C(void);
extern s16 dungeonCheckActorFloorTrap(s32, s32);
extern u8 D_8016B778[];

void func_8016DAA4(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (func_800AC82C() && dungeonCheckActorFloorTrap(first, second) > 0) {
        owner->callback = D_8016B778;
    }
}
