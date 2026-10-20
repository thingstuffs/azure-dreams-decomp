#include "common.h"

extern u8 D_80701DFC[];
extern void shop_advance_entry_step(s32 index);
extern s32 shop_test_indexed_flag(u16 value);

/* Select the first table entry whose value check returns zero. */
void shop_find_first_eligible_entry(void) {
    s32 index = 0;
    s32 offset = 0;

    while (shop_test_indexed_flag(*(u16 *)&D_80701DFC[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    shop_advance_entry_step(index);
}
