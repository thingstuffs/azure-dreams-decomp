#include "common.h"

extern s32 func_800188EC(void);
extern void *func_80019DFC(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_8001ADE0(s32 arg0);

extern s32 D_8001BB3C;
extern s32 D_8001C354;
extern s32 D_8001E3B0;
extern s32 D_8001E59B;

// Returns the lookup result or an alternate pointer selected by the current state.
void *func_80016F84(s32 lookupValue, s32 unused, s32 lookupOption) {
    void *lookupResult;

    lookupResult = func_80019DFC(&D_8001BB3C, &D_8001C354, lookupValue, lookupOption);
    if (func_800188EC() != 0) {
        if (func_8001ADE0(0xD53) == 0) {
            return &D_8001E3B0;
        }
        return &D_8001E59B;
    }
    return lookupResult;
}
