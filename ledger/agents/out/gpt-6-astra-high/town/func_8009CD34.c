#include "common.h"

extern void func_80033D08(void *arg0);
extern void func_80098928(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80082660;

/* Clean up the actor, clear its indexed flag, and complete its current action. */
void func_8009A494(void *actor, s32 motionState, s32 completionArg) {
    func_80033D08(actor);
    *(((*(s32 *)((u8 *)actor + 0x40)) * 8) + &D_80082660) = 0;
    func_80098928(actor, motionState, completionArg);
}
