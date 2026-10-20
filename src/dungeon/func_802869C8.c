#include "dungeon/level/generate.h"

s32 try_add_second_tower_entry(s16 entry_index) {
    u8 *entry;
    u8 *entries;

    if (D_80012090[0] == 0) {
        if (((s16 *)D_8008146C)[0] == 2) {
            if (test_resident_bit(0xA2) != 0) {
                if ((count_matching_packed_entity_keys(0xC, 8) << 0x10) != 0) {
                    entries = (u8 *)((s16 *)D_800E3CD8);
                    entry = entries;
                    entry += ((entry_index << 0x10) >> 0xD);
                    *(s16 *)(entry + 0) = 4;
                    *(s16 *)(entry + 2) = 8;
                    *(s16 *)(entry + 4) = 8;
                    *(s16 *)(entry + 6) = 0;
                    cycle_map_cell_flags(8, 8, 0x20);
                    return 1;
                }
            }
        }
    }
    return 0;
}
