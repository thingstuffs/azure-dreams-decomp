#include "script_symbols.h"
#include "common.h"
#include "shared/object_flags.h"

extern s32 set_resident_bitmap_bit(s32 bit_id);
extern s32 serch_item_plown(s32 first_value, s32 second_value);

/* Trigger action 0xAB and mark the record finished when the condition check succeeds. */
void trigger_action_and_finish_record(u16 *record) {
    if (serch_item_plown(0xC, 0xF) != 0) {
        set_resident_bitmap_bit(F_guy_sword_pickup);
        record[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
