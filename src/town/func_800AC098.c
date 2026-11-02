#include "script_symbols.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"
#include "engine/object.h"
#include "town.h"
#include "town/shop/item.h"

/*
 * When serch_item_plown finds item kind 1 and ID 0x12, sets F_ultima_egg_pickup and flags the
 * record for removal.
 */
void set_resident_flag_when_item_present(u16 *record) {
    if (serch_item_plown(1, 0x12) != 0) {
        set_resident_bitmap_bit(F_ultima_egg_pickup);
        record[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
