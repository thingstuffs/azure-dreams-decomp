#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/shop.h"

/*
 * Searches slot_count addresses starting at slot_addr in steps of four, returning the zero-based
 * matching index or -1 for an empty or unmatched range.
 */
s32 find_slot_index_by_address(void *target_addr, void *slot_addr, s32 slot_count) {
    s32 slot_index;

    slot_index = 0;
    if (slot_count > 0) {
        while (1) {
            if (target_addr == slot_addr) {
                return slot_index;
            }
            slot_index += 1;
            if (slot_index >= slot_count) {
                break;
            }
            slot_addr += 4;
        }
    }
    return -1;
}
