#include "common.h"

typedef s32 M2C_UNK;

extern s32 townResolveEntryFlag();
extern s32 townApplyEntryPosition();
extern void townSetScriptFlagBit();
extern M2C_UNK D_8001BB94;
extern M2C_UNK D_8001C358;
extern u8 D_8001E891;

/* Resolve a table result and apply the conditional override or fallback action. */
s32 townDispatchEntryOrProcessFallback(s32 context, s32 unused, M2C_UNK entry_key) {
    M2C_UNK result;

    result = townApplyEntryPosition(&D_8001BB94, &D_8001C358, context, entry_key);
    if (townResolveEntryFlag(&D_8001BB94, context, entry_key) != 0) {
        return (s32)&D_8001E891;
    }
    townSetScriptFlagBit(0x1457);
    return result;
}
