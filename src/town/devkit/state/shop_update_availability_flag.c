#include "common.h"
#include "town/shop/state.h"

extern void clear_indexed_flag(s32);

/* Update flag 0x24C based on flags 0x20C and 0x268. */
void update_combined_flag(void) {
    if ((test_indexed_flag(0x20C) == 0) && (test_indexed_flag(0x268) == 0)) {
        set_indexed_flag(0x24C);
        return;
    }
    clear_indexed_flag(0x24C);
}
