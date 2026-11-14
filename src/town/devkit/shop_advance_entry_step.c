#include "common.h"
#include "town/shop/state.h"
#include "town/devkit.h"
#include "town/devkit/state.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_80701DCE[];
extern TownPair devkit_shop_flag_links[];

extern void clear_indexed_flag(s32 value);

/* Advance the selected flag row and process entry zero when required. */
s32 advance_selected_flag_row(s32 index) {
    if (test_indexed_flag(D_80701DCE[0]) == 0 &&
        test_indexed_flag(0x1F9) != 0) {
        if (test_flag_list_terminator(index) != 0) {
            set_indexed_flag(devkit_shop_flag_links[index].field_0);
            clear_indexed_flag(0x1F9);
            return advance_clear_flag_row();
        }
        set_entry_bit_flag(index, 0);
        return index;
    }
    set_entry_bit_flag(index, 0);
    return index;
}
