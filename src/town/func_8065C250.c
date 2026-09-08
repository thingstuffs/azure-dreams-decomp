#include "common.h"

extern s8 D_80016000[];
extern s32 D_800183D0[];
extern s32 D_800183D8[];

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

// Calls two callbacks with shared arguments, passing the first callback's result to the second.
void func_8065C250(void) {
    s8 *dispatchRoot = D_80016000;
    s32 *sharedArguments = D_800183D8;
    s32 callbackResult;

    callbackResult = FIELD(FIELD(FIELD(dispatchRoot, void **, 0), void **, 0x20), s32 (**)(s32, s32 *), 0x48)(D_800183D0[0], sharedArguments);
    FIELD(FIELD(FIELD(dispatchRoot, void **, 0), void **, 0x20), void (**)(s32 *, s32), 0x3C)(sharedArguments, callbackResult);
}
