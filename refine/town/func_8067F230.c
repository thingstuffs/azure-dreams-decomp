#include "common.h"

typedef s32 M2C_UNK;

s32 func_80017A54();
M2C_UNK *func_80017B0C();
extern M2C_UNK D_80018770;
extern M2C_UNK D_800188BC;
extern M2C_UNK D_8001A714;

/* Looks up an entry, with a conditional override for entry 0x26. */
M2C_UNK *func_8067F230(s32 lookup_key, s32 unused, s32 entry_id) {
    M2C_UNK *entry;

    entry = func_80017B0C(&D_80018770, &D_800188BC, lookup_key, entry_id);
    if (func_80017A54(&D_80018770, lookup_key, entry_id) != 0) {
        if (entry_id == 0x26) {
            entry = &D_8001A714;
        }
    }
    return entry;
}
