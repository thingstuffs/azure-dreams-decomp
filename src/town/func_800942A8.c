#include "common.h"

extern void func_80095C80(void *arg1);
extern void func_80095094(void *arg1);
extern s16 func_80095978(void *arg1, void *arg2);
extern void func_80095A94(void *arg1, s16 arg2, void *arg3);
extern void func_80094378(void *arg0, void *arg1, s32 arg2);
extern void func_800940D0(void *arg0, void *arg1, s32 arg2);

extern u8 D_800FE488[];
extern u8 D_800CFCEF[];

/* Update the object, check its target value, and advance the countdown. */
void func_80091A08(void *state, void *object, s32 context) {
    s16 target_value;
    u16 countdown;

    func_80095C80(object);
    func_80095094(object);
    target_value = func_80095978(object, D_800FE488);
    if (target_value - *(s16 *)((u8 *)object + 0xA) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(state, object, context);
            return;
        }
    } else {
        if (D_800CFCEF[0] == 0) {
            func_80095A94(object, target_value, D_800FE488);
        }
    }

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        func_800940D0(state, object, context);
    }
}
