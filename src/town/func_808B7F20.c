/* Relinked copy of town/func_808781C8 (func_808781C8.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_00003F5A[];
extern TownPair D_00003F88[];

extern s32 skip_entries_accepted_next_entry(s32 index);
extern void set_flag_entry_has_bit(s32 index, s32 value);
extern s32 select_table_entry_zero(void);
extern void func_80003BCC(u16 value);
extern void func_80003C1C(s32 value);
extern s32 test_indexed_flag_treating_indices(u16 value);

/* Advance the shop entry at `index`: start its 0x1F9 step when eligible, otherwise just clear it. */
s32 advance_shop_entry_index_start(s32 index) {
    if (test_indexed_flag_treating_indices(D_00003F5A[0]) == 0 &&
        test_indexed_flag_treating_indices(0x1F9) != 0) {
        if (skip_entries_accepted_next_entry(index) != 0) {
            func_80003BCC(D_00003F88[index].field_0);
            func_80003C1C(0x1F9);
            return select_table_entry_zero();
        }
        set_flag_entry_has_bit(index, 0);
        return index;
    }
    set_flag_entry_has_bit(index, 0);
    return index;
}
