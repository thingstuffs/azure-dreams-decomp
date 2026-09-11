#include "common.h"

extern s32 func_800175B0();
extern s32 func_80019A8C();
extern s32 D_80019BB0;

/* Set state 1 and return whether the initial check passes and the count is at least 20. */
s32 func_80017848(void) {
    D_80019BB0 = 1;
    if (func_800175B0() != 0) {
        if (func_80019A8C() >= 20) {
            return 1;
        }
    }
    return 0;
}
