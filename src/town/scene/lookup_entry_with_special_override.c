#include "modules/town_ovl_5ff1d0.h"
#include "town/scene.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

/*
 * Looks up D_80018770 with D_800188BC and substitutes D_8001A714 for entry ID 0x26 only when the
 * follow-up check succeeds.
 */
s32 *lookup_entry_with_special_override(s32 lookup_key, s32 unused, s32 entry_id) {
    s32 *entry;

    entry = apply_entry_position(&D_80018770, &D_800188BC, lookup_key, entry_id);
    if (resolve_entry_flag(&D_80018770, lookup_key, entry_id) != 0) {
        if (entry_id == 0x26) {
            entry = &D_8001A714;
        }
    }
    return entry;
}
