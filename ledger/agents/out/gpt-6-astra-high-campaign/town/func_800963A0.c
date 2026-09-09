#include "common.h"

extern void func_80093D48(void *, s32, s32);
extern void func_8009451C(void *, s32, s32);
extern s32 func_80095840(void *, s32 *);
extern s32 D_800CFCB4[];

/* Dispatch the actor's action using its cached entry or the entry lookup result. */
void func_80093B00(void *actor, s32 position, s32 context) {
    s32 cached_entry;
    s32 action_result;

    cached_entry = *(s32 *)((u8 *)actor + 0x2C);
    if (cached_entry != 0) {
        D_800CFCB4[4] = cached_entry;
        D_800CFCB4[6] = 0;
        func_8009451C(actor, position, context);
    } else {
        action_result = func_80095840(actor, D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(actor, position, context);
            } else {
                func_80093D48(actor, position, context);
            }
        } else {
            func_80093D48(actor, position, context);
        }
    }
}
