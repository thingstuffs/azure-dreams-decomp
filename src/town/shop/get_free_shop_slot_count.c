#include "common.h"

/* Returns 20 minus the value from count_shop_entries. */
s32 get_free_shop_slot_count(void) {
    return 0x14 - count_shop_entries();
}
