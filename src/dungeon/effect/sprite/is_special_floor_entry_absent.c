#include "shared/dungeon_item_entries.h"
#include "dungeon/effect/sprite.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Return whether the 64-entry table lacks the byte pair 1, 0x12. */
s32 ground_items_lack_special_pair(void) {
    s32 entry_index;
    s32 key_low;
    s32 key_high;
    u8 *table_or_result;
    u8 *entry;

    entry_index = 0x3F;
    key_high = 0x12;
    key_low = 1;
    table_or_result = (u8 *)((s32 *)dungeon_ground_items);
    entry = table_or_result + 0xFC;
    for (;;) {
        if ((entry[1] != key_high) || (entry[0] != key_low)) {
            entry_index -= 1;
            entry -= 4;
            if (entry_index < 0) {
                table_or_result = (u8 *)1;
            } else {
                continue;
            }
        } else {
            table_or_result = (u8 *)0;
        }
        break;
    }
    return (s32)table_or_result;
}
