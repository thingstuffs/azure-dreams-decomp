#include "common.h"
#include "shared/object_flags.h"

extern s32 func_80033AA8(s32 bit_id);
extern s32 serch_item_plown(s32 first_value, s32 second_value);

/* Trigger action 0xAB and mark the record finished when the condition check succeeds. */
void func_800A9778(u16 *record) {
    if (serch_item_plown(0xC, 0xF) != 0) {
        func_80033AA8(0xAB);
        record[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
