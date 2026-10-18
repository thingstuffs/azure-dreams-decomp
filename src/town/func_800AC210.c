#include "common.h"

s32 test_resident_bitmap_bit();                         /* extern */
extern s16 D_800D1054[];

/* Checks whether a slot's indexed value is at least three or slot three passes the helper check. */
s32 check_slot_threshold_or_fallback(s32 slot) {
    s16 *entry_indices;
    u8 *data_page;
    s32 entry_index;

    entry_indices = D_800D1054;
    entry_index = entry_indices[slot];
    data_page = (u8 *) 0x80010000;
    if (data_page[(entry_index * 4) + 0x35C4] >= 3U) {
        return 1;
    }
    if (slot == 3) {
        return test_resident_bitmap_bit(0x4FB) == 0;
    }
    return 0;
}
