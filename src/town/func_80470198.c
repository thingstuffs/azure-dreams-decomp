#include "modules/town_ovl_3ef1c8.h"

s32 func_80017198(s32 slot_index, s32 slot_value) {
    if (func_8001A510(0x799) == 0) {
        func_80019618(slot_index, slot_value);
        return 1;
    }

    if (func_8001A7F8() < 0x1A) {
        func_80019814(slot_index, slot_value);
        return;
    }

    func_80019928(slot_index, slot_value);
}
