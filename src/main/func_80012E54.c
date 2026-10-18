#include "common.h"

s32 test_resident_bitmap_bit();                             /* extern */
extern s16 D_80028010[8];

/* Return a bitmask of the eight entries for which test_resident_bitmap_bit is nonzero. */
s32 card_boot_build_eight_entry_presence_mask(void) {
    s16 *entry;
    s32 index;
    s32 result_mask;
    s32 bit;

    result_mask = 0;
    index = 0;
    bit = 1;
    entry = D_80028010;
    do {
        if (test_resident_bitmap_bit(*entry) != 0) {
            result_mask += bit << index;
        }
        index += 1;
        entry += 1;
    } while (index < 8);
    return result_mask;
}
