#include "dungeon/level/generate.h"

void compact_generation_regions(void) {
    s8 *read_entry;
    s8 *write_entry;
    s32 entry_count;
    s32 entry_index;

    entry_index = 0;
    entry_count = 0;
    read_entry = (s8 *)D_800E2970;
    write_entry = (s8 *)D_800E2970;
    do {
        if (*(s16 *)(read_entry + 0xA) != 0) {
            if (entry_index != entry_count) {
                *(floor_generate_isolated_802846EC_DungeonEntry *)write_entry = *(floor_generate_isolated_802846EC_DungeonEntry *)read_entry;
            }
            write_entry += 0x14;
            entry_count += 1;
        }
        entry_index += 1;
        read_entry += 0x14;
    } while (entry_index < 0x24);

    entry_index = entry_count;
    if (entry_count < 0x24) {
        do {
            D_800E2970[entry_index].unk_0A = 0;
            D_800E2970[entry_index].unk_0E = 0;
            D_800E2970[entry_index].unk_10 = 0;
        } while (++entry_index < 0x24);
    }
    ((s16 *)D_8008146E)[0] = entry_count;
}
