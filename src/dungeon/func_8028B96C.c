#include "dungeon/level/spawn.h"

void clear_dungeon_cell_entries(void) {
    s32 entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        ((int *)D_800E3548)[entry_index] = 0;
    }
}
