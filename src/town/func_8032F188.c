#include "common.h"

extern s32 townSetScriptFlagBit();
extern s32 townClearScriptFlagBit();

/* Update flags using the record and indexed entry, then return success. */
s32 townUpdateEntryFlags(void *record, s32 entry_index) {
    townClearScriptFlagBit(*(s16 *)((s8 *)record + 0x18));
    townSetScriptFlagBit(*(s16 *)((entry_index * 0x10) + *(s32 *)((s8 *)record + 0x10) + 0xC));
    return 1;
}
