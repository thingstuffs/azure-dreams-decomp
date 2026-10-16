#include "modules/dungeon_floor_spawns.h"

void clearDungeonCellEntries(void) {
    s32 entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        ((int *)D_800E3548)[entry_index] = 0;
    }
}
