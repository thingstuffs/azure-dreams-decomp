#include "common.h"

extern s32 townGetReferencedObjectActiveFlag(void);
extern void *townApplyEntryPosition(void *entries, void *object, s32 context, s32 selection);
extern s32 townGetScriptFlagMask(s32 flagIndex);

extern s32 D_8001BB3C;
extern s32 D_8001C354;
extern s32 D_8001E3B0;
extern s32 D_8001E59B;

// Returns the lookup result or an alternate pointer selected by the current state.
void *townDispatchOrSelectStateData(s32 lookupValue, s32 unused, s32 lookupOption) {
    void *lookupResult;

    lookupResult = townApplyEntryPosition(&D_8001BB3C, &D_8001C354, lookupValue, lookupOption);
    if (townGetReferencedObjectActiveFlag() != 0) {
        if (townGetScriptFlagMask(0xD53) == 0) {
            return &D_8001E3B0;
        }
        return &D_8001E59B;
    }
    return lookupResult;
}
