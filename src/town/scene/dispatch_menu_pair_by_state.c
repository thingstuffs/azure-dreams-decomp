#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"

/* Applies the slot value while flag 0x798 is clear; otherwise dispatches by the helper threshold of 26. */
s32 dispatch_menu_pair_by_798_state(void *slot_index, s32 slot_value) {
    s32 result;

    if (func_8001A510(F_sbs22_pad28) == 0) {
        apply_signed_value_to_indexed_entry(slot_index, slot_value);
        return 1;
    }

    if (func_8001A7F8() < 0x1A) {
        result = func_80019814(slot_index, slot_value);
    } else {
        result = func_80019928(slot_index, slot_value);
    }
    return result;
}
