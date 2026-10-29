#include "script_symbols.h"
#include "common.h"
#include "shared/object_flags.h"
#include "engine/object.h"
#include "town/map.h"
#include "town/shop/item.h"

/* Trigger action 0xAB and mark the record finished when the condition check succeeds. */
void trigger_action_and_finish_record(u16 *record) {
    if (serch_item_plown(0xC, 0xF) != 0) {
        set_resident_bitmap_bit(F_guy_sword_pickup);
        record[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
