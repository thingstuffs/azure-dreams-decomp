#include "script_symbols.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"

extern s32 set_resident_bitmap_bit(s32 bit_id);
extern s32 serch_item_plown(s32 first_value, s32 second_value);

void set_resident_flag_when_item_present(u16 *record) {
    if (serch_item_plown(1, 0x12) != 0) {
        set_resident_bitmap_bit(F_ultima_egg_pickup);
        record[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
