#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town/scene/motion.h"

extern u8 D_800189D8[];
extern u8 D_80019104[];
extern u8 D_8001A212[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

/* Looks up an entry and applies conditional overrides for variants 45 through 47. */
s32 lookup_variant_with_flag_overrides(s32 entry_id, s32 unused, s32 variant_id)
{
    s32 default_result;

    default_result = apply_entry_position(D_800189D8, D_80019104, entry_id, variant_id);

    if (variant_id == 45 && resolve_entry_flag(D_800189D8, entry_id, 45)) {
        clear_script_flag_bit(F_sbs35_pad03);
        return (s32)D_8001A212;
    }
    if (variant_id == 46 && resolve_entry_flag(D_800189D8, entry_id, 46)) {
        return (s32)D_8001ABCC;
    }
    if (variant_id == 47 && resolve_entry_flag(D_800189D8, entry_id, 47)) {
        return (s32)D_80019397;
    }
    return default_result;
}
