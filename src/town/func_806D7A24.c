#include "common.h"

extern u8 D_80018980[];
extern u8 D_80019104[];
extern u8 D_80019397[];
extern u8 D_800197D0[];

extern void *func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);

/* Looks up an entry and applies conditional overrides for IDs 0x2D and 0x2F. */
void *func_80016224(s32 lookup_key, s32 unused, s32 entry_id)
{
    void *entry;

    entry = func_80017B0C(D_80018980, D_80019104, lookup_key, entry_id);
    if (entry_id == 0x2D && func_80017A54(D_80018980, lookup_key, 0x2D) != 0) {
        return D_800197D0;
    }
    if (entry_id == 0x2F && func_80017A54(D_80018980, lookup_key, 0x2F) != 0) {
        return D_80019397;
    }
    return entry;
}
