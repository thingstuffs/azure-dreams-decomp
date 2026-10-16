#include "common.h"

s32 func_80017A54();
s32 *func_80017B0C();
extern s32 D_80018790;
extern s32 D_800188BC;
extern s32 D_8001A854;

/* Looks up an entry, with a conditional override for entry 0x26. */
s32 *func_8067F320(s32 lookup_key, s32 unused, s32 entry_id) {
    s32 *entry;

    entry = func_80017B0C(&D_80018790, &D_800188BC, lookup_key, entry_id);
    if (func_80017A54(&D_80018790, lookup_key, entry_id) != 0) {
        if (entry_id == 0x26) {
            entry = &D_8001A854;
        }
    }
    return entry;
}
