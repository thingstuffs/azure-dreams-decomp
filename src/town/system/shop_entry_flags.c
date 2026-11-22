/* Toggle shop entry flags and sum the values of selected entries. */

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "m2c_compat.h"
#include "town/shop/grid_menu.h"
#include "slus.h"
#include "town/system.h"



/* Toggle the selected entry flag 0x20 when flag 0x80 is clear. */

/* Toggles bit 0x20 in the selected four-byte entry unless its byte-3 flags include 0x80. */
void toggle_selected_entry_flag(GridMenuObject *state) {
    DungeonItemEntry *entries = state->entry_base;
    s32 index = state->selected_index;
    u8 flags = entries[index].unk_03;
    if (!(flags & 0x80)) {
        entries[index].unk_03 = (u8)(flags ^ 0x20);
    }
}


/* Sum results for flagged entries using the selected mode. */
s32 sum_flagged_entry_prices(DungeonItemEntry *entry, s32 mode) {
    register s32 total;

    total = 0;
    if (entry->kind != 0) {
        do {
            if (entry->unk_03 & 0x20) {
                if (mode == 0) {
                    total += get_item_buy_money(entry);
                } else {
                    total += get_item_sell_money(entry);
                }
            }
            entry++;
        } while (entry->kind != 0);
    }
    return total;
}
