/* Relink of matched town/func_8032CFFC; every changed retail word is a paired relocation. */
#define D_8001BB7C D_8001BB84
#include "common.h"

typedef s32 M2C_UNK;

extern s32 townResolveEntryFlag();
extern s32 townApplyEntryPosition();
extern M2C_UNK D_8001BB84;
extern M2C_UNK D_8001C358;
extern u8 D_8001E891;

/* Process the selected entry and return its result or the override pointer. */
s32 func_8001789C(s32 context, s32 unused, M2C_UNK entry_id) {
    M2C_UNK entry_result;

    entry_result = townApplyEntryPosition(&D_8001BB84, &D_8001C358, context, entry_id);
    return townResolveEntryFlag(&D_8001BB84, context, entry_id) != 0
        ? (s32)&D_8001E891
    : entry_result;
}
