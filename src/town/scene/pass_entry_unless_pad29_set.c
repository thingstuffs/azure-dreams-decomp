#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/state.h"

/* Applies the slot value while flag 0x799 is clear; otherwise dispatches by the helper threshold of 26. */
s32 pass_entry_unless_pad29_set(void *slot_index, s32 slot_value) {
    s32 result;

    if (get_script_flag_mask(F_sbs22_pad29) == 0) {
        set_flag_from_indexed_entry(slot_index, slot_value);
        return 1;
    }

    if (get_town_state_count() < 0x1A) {
        result = apply_selected_entry_values(slot_index, slot_value);
    } else {
        result = process_checked_entry(slot_index, slot_value);
    }
    return result;
}
