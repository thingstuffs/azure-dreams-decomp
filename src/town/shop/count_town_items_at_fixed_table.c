#include "common.h"
#include "shared/game_state.h"
#include "town/shop.h"

/* Count nonzero words in the fixed table until its zero terminator. */
s32 count_town_items_at_fixed_table(void) {
    DungeonItemEntry **entry;
    s32 count;

    entry = GAME_STATE->item_list;
    count = 0;
    if (entry[0] != 0) {
        do {
            entry = entry + 1;
            count++;
        } while (entry[0] != 0);
    }
    return count;
}
