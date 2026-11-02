#include "common.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern u8 D_80018980[];
extern u8 D_80019104[];
extern u8 D_80019397[];
extern u8 D_800197D0[];

/* Looks up an entry and applies conditional overrides for IDs 0x2D and 0x2F. */
void *lookup_variant_with_special_overrides(s32 lookup_key, s32 unused, s32 entry_id)
{
    void *entry;

    entry = apply_entry_position(D_80018980, D_80019104, lookup_key, entry_id);
    if (entry_id == 0x2D && resolve_entry_flag(D_80018980, lookup_key, 0x2D) != 0) {
        return D_800197D0;
    }
    if (entry_id == 0x2F && resolve_entry_flag(D_80018980, lookup_key, 0x2F) != 0) {
        return D_80019397;
    }
    return entry;
}
