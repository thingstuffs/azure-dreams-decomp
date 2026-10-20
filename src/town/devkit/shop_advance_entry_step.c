#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_80701DCE[];
extern TownPair D_80701DFC[];

extern s32 shop_skip_accepted_entries(s32 index);
extern void shop_set_entry_step_flag(s32 index, s32 value);
extern s32 shop_find_first_eligible_entry(void);
extern void shop_set_indexed_flag(u16 value);
extern void shop_clear_indexed_flag(s32 value);
extern s32 shop_test_indexed_flag(u16 value);

/* Advance the shop entry at `index`: start its 0x1F9 step when eligible, otherwise just clear it. */
s32 shop_advance_entry_step(s32 index) {
    if (shop_test_indexed_flag(D_80701DCE[0]) == 0 &&
        shop_test_indexed_flag(0x1F9) != 0) {
        if (shop_skip_accepted_entries(index) != 0) {
            shop_set_indexed_flag(D_80701DFC[index].field_0);
            shop_clear_indexed_flag(0x1F9);
            return shop_find_first_eligible_entry();
        }
        shop_set_entry_step_flag(index, 0);
        return index;
    }
    shop_set_entry_step_flag(index, 0);
    return index;
}
