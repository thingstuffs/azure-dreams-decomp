#include "modules/town_ovl_3ef1c8.h"

s32 dispatch_menu_pair_by_798_state(s32 slot_index, s32 slot_value) {
    if (func_8001A510(0x798) == 0) {
        apply_signed_value_to_indexed_entry(slot_index, slot_value);
        return 1;
    }

    if (func_8001A7F8() < 0x1A) {
        func_80019814(slot_index, slot_value);
        return;
    }

    func_80019928(slot_index, slot_value);
}
