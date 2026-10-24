#include "town/shop.h"
#include "common.h"

/* Returns 20 minus the value from count_shop_entries. */
s32 count_free_item_slots(void) {
    return 0x14 - count_town_items();
}
