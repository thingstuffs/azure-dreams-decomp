#include "modules/dungeon_ovl_d54c.h"

s32 find_resource_index_by_key(s32 first_byte, s32 second_byte, s32 halfword_value) {
    s32 entry_index;
    s32 end_marker;
    s32 scan_end_marker;
    s8 *entry_table;
    s8 *entry;

    entry_table = D_800CF720;
    entry_index = 0;
    end_marker = -1;
    if (entry_table[1] != end_marker) {
        scan_end_marker = end_marker;
        entry = entry_table;
check_entry:
        if ((first_byte == entry[0]) && (second_byte == entry[1]) && (halfword_value == *(s16 *)(entry + 2))) {
            return entry_index;
        }
        entry += 8;
        entry_index += 1;
        if (entry[1] != scan_end_marker) {
            goto check_entry;
        }
    }
    return entry_index - 0x80000000;
}
