#include "modules/town_ovl_5ff1d0.h"

s32 *lookup_entry_with_special_override(s32 lookup_key, s32 unused, s32 entry_id) {
    s32 *entry;

    entry = func_80017B0C(&D_80018770, &D_800188BC, lookup_key, entry_id);
    if (func_80017A54(&D_80018770, lookup_key, entry_id) != 0) {
        if (entry_id == 0x26) {
            entry = &D_8001A714;
        }
    }
    return entry;
}
