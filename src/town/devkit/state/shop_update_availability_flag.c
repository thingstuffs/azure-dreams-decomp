#include "common.h"

extern void shop_set_indexed_flag(s32);
extern void shop_clear_indexed_flag(s32);
extern s32 shop_test_indexed_flag(s32);

/* Update flag 0x24C based on flags 0x20C and 0x268. */
void shop_update_availability_flag(void) {
    if ((shop_test_indexed_flag(0x20C) == 0) && (shop_test_indexed_flag(0x268) == 0)) {
        shop_set_indexed_flag(0x24C);
        return;
    }
    shop_clear_indexed_flag(0x24C);
}
