#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern u8 D_800189AC[16];
extern u8 scene_event_lookup_context[16];
extern u8 D_80018FFC[16];

/* Looks up an entry or selects a fallback, with a special case for entry 0x1C. */
void *lookup_entry_fallback_special_case(s32 lookup_key, s32 unused, s32 entry_id) {
    void *entry;

    entry = get_special_data_for_low_value_id(entry_id);
    if (entry != 0) {
        return entry;
    }
    set_script_flag_bit(F_sb34_00);
    entry = apply_entry_position(&D_800189AC, &scene_event_lookup_context, lookup_key, entry_id);
    if ((entry_id == 0x1C) && (resolve_entry_flag(&D_800189AC, lookup_key, 0x1C) != 0)) {
        entry = &D_80018FFC;
    }
    return entry;
}
