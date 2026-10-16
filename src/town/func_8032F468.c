#include "common.h"

extern void townSetScriptFlagBit(s32 bit_index);
extern void townClearScriptFlagBit(s32 bit_index);
extern s32 townGetScriptFlagMask(s32 flagIndex);

// Processes the selected entry if the object's handle passes its status check.
s32 townProcessCheckedEntry(void *object, s32 entryIndex)
{
    s32 processed;

    if (townGetScriptFlagMask(*(s16 *)((s8 *)object + 0x18)) == 0) {
        processed = 0;
    } else {
        townSetScriptFlagBit(*(s16 *)(*(s32 *)((s8 *)object + 0x10) + entryIndex * 0x10 + 0xC));
        townClearScriptFlagBit(*(s16 *)((s8 *)object + 0x18));
        processed = 1;
    }
    return processed;
}
