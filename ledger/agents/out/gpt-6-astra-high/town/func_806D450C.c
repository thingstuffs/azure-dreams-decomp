#include "common.h"

extern s32 func_8001868C();
extern void func_80018594();
extern s32 func_800177CC();
extern void func_80016FD0();

/* Apply the object's flag when flag 0x145B is set, then process its action and handle failure. */
s32 func_806D450C(void *object, s32 actionParameter) {
    if (func_8001868C(0x145B) != 0) {
        func_80018594(*(s16 *)((u8 *)object + 0x18));
    }
    if (func_800177CC(object, actionParameter) == 0) {
        func_80016FD0();
        return 0;
    }
    return 1;
}
