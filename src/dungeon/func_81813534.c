#include "common.h"

extern void func_8004E99C(s32);

/* Calls func_8004E99C on nine referenced values, clearing the first eight. */
void func_80028534(void *state) {
    s32 **value_slot;
    s32 slot_index;

    slot_index = 6;
    value_slot = state + 0x18;
    do {
        slot_index += 1;
        func_8004E99C(**value_slot);
        **value_slot = 0;
        value_slot += 1;
    } while (slot_index < 0xE);
    func_8004E99C(**(s32 **)((u8 *)state + 0x38));
}
