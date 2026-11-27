#include "common.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town/scene.h"

extern u8 grandpa_house_three_override_response_entries[];
extern u8 D_80019104[];
extern u8 D_80019AB6[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

/* Looks up an entry, substituting fixed data for matching IDs 45 through 47. */
s32 select_response_with_three_overrides(TownObjectSet *lookup_key, s32 unused, s32 entry_id)
{
    s32 result;

    result = apply_entry_position(grandpa_house_three_override_response_entries, D_80019104, lookup_key, entry_id);

    if (entry_id == 45 && resolve_entry_flag(grandpa_house_three_override_response_entries, lookup_key, 45)) {
        return (s32)D_80019AB6;
    }
    if (entry_id == 46 && resolve_entry_flag(grandpa_house_three_override_response_entries, lookup_key, 46)) {
        return (s32)D_8001ABCC;
    }
    if (entry_id == 47 && resolve_entry_flag(grandpa_house_three_override_response_entries, lookup_key, 47)) {
        return (s32)D_80019397;
    }
    return result;
}
