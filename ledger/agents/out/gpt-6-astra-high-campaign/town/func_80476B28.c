#include "common.h"

extern void func_800197D8(s32);
extern void func_80019850(s32);
extern s32 func_800198D0(s32);
extern s32 D_80019BB0;

/* Set state 5 and apply the two updates when check 0x145D succeeds. */
s32 func_80017B28(void) {
    D_80019BB0 = 5;
    if (func_800198D0(0x145D) != 0) {
        func_800197D8(0x1455);
        func_80019850(0x11FA);
        return 0;
    }
    return 1;
}
