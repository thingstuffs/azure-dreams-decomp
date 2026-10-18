#include "modules/dungeon_ovl_1831cd8.h"

s32 count_menu_entry_pair_matches(s32 target_value, s32 prefix_value) {
    s32 index;
    s32 count;
    u8 value;
    u8 *page = (u8 *)0x80010000;

    count = 0;
    for (index = 0; index < 0x40; index++) {
        value = page[0x57D2 + index * 0x13];
        if (value == 0) {
            break;
        }
        if ((value == target_value) && (page[0x57D1 + index * 0x13] == prefix_value)) {
            count++;
        }
    }
    return count;
}
