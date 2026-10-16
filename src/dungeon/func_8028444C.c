#include "modules/dungeon_floor_generate.h"

void dungeonClearGenerationCellGrid(void) {
    s8 *entry_start;
    s8 *entry_tail;
    s32 entries_left;

    entry_start = ((u8 *)D_800EA000);
    entries_left = 0x1000;
    entry_tail = entry_start + 2;
    do {
        entries_left -= 1;
        ((floor_generate_isolated_8028444C_S_8001744C_0 *)entry_start)->unk_00 = 0;
        ((floor_generate_isolated_8028444C_S_8001744C_1 *)entry_tail)->unk_02 = 0;
        ((floor_generate_isolated_8028444C_S_8001744C_1 *)entry_tail)->unk_00 = 0;
        entry_tail += 6;
        entry_start += 6;
    } while (entries_left > 0);
}
