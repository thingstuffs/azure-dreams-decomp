#include "common.h"

extern s32 townGetScriptFlagMask(s16 flagIndex);
extern void townSetCurrentEntryScriptFlag(void);
extern void townSetScriptFlagBit(s32 bit_index);
extern u8 D_8001E6F8[];
extern u8 D_8001F4CD[];
extern u8 D_8001F4E2[];

// Returns event-specific data, running the fallback action when the object check fails.
void *townSelectEventDataAndFallback(void *object, s32 unused, s32 eventCode) {
    if (eventCode == 0x25) {
        if (townGetScriptFlagMask(*(s16 *)((u8 *)object + 0x18)) != 0) {
            return D_8001F4E2;
        }
        townSetCurrentEntryScriptFlag();
        townSetScriptFlagBit(0x145D);
        return D_8001E6F8;
    }
    if (eventCode == 0x44) {
        return D_8001F4CD;
    }
    return 0;
}
