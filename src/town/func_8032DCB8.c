#include "common.h"

extern s32 townHasMatchingEntryResult(s32, s32);
extern void townSetCurrentEntryScriptFlag(void);
extern s32 townApplySelectedEntryValues(s32, s32);
extern void townClearScriptFlagBit(s32);

/* Processes the selected context entry and applies a fallback value on failure. */
s32 townProcessContextEntryWithFallback(s32 entryContext, s32 entryIndex)
{
    if (townHasMatchingEntryResult(13, 1) != 0) {
        townSetCurrentEntryScriptFlag();
    }

    if (townApplySelectedEntryValues(entryContext, entryIndex) == 0) {
        townClearScriptFlagBit(0xD7F);
        return 0;
    }

    return 1;
}
