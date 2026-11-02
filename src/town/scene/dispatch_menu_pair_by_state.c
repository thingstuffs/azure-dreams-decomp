#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"

/* Applies the slot value while flag 0x798 is clear; otherwise dispatches by the helper threshold of 26. */
s32 dispatch_menu_pair_by_798_state(void *slot_index, s32 slot_value) {
    s32 result;

    if (func_8001A510(F_sbs22_pad28) == 0) {
        pass_indexed_entry(slot_index, slot_value);
        return 1;
    }

    if (func_8001A7F8() < 0x1A) {
        result = apply_selected_entry_values(slot_index, slot_value);
    } else {
        result = process_checked_entry(slot_index, slot_value);
    }
    return result;
}
