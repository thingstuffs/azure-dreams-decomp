#include "common.h"
#include "town/shop/item_lookup.h"

extern s32 count_nonzero_entries(void *entries);

/* get_item_chk: Return the item index, or -1 when it is at least 20. */
s32 get_item_chk(void) {
    s32 item_index;
    s32 invalid_index;

    item_index = count_nonzero_entries((void *)0x8001029C);
    invalid_index = -1;
    if (item_index >= 20) {
        return invalid_index;
    }
    return item_index;
}
