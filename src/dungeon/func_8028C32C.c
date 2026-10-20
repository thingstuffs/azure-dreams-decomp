#include "dungeon/level/spawn.h"

void clear_dungeon_object_entries(void) {
    s32 entry_index;

    for (entry_index = 0x1F; entry_index >= 0; entry_index--) {
        ((int *)D_800E3648)[entry_index] = 0;
    }
}
