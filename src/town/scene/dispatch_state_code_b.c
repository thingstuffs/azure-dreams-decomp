#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/state.h"

/* Applies the slot value while flag 0x799 is clear; otherwise dispatches by the helper threshold of 26. */
s32 dispatch_by_state_code_0x799(void *slot_index, s32 slot_value) {
    s32 result;

    if (get_script_flag_mask(F_sbs22_pad29) == 0) {
        pass_indexed_entry(slot_index, slot_value);
        return 1;
    }

    if (get_linked_record_field_2_d_60() < 0x1A) {
        result = apply_selected_entry_values(slot_index, slot_value);
    } else {
        result = process_checked_entry(slot_index, slot_value);
    }
    return result;
}
