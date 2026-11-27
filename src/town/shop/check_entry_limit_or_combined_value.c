#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "town/shop.h"
#include "town/shop/state.h"

/* Checks whether the entry bypasses the limit or its combined value is below 20. */
s32 check_entry_limit_or_combined_value(GridMenuObject *entry) {
    s32 total;

    if (entry->price_mode == 0) {
        if ((u32) (entry->entry_base[entry->selected_index].kind - 0x17) < 2U) {
            return 1;
        }
        total = count_town_items_at_fixed_table();
        total += count_equipped_entries(entry->entry_base);
        return total < 20;
    }
    return 1;
}
