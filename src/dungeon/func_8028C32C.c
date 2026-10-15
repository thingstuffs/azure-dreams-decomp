#include "modules/dungeon_floor_spawns.h"

void func_8001F32C(void) {
    s32 entry_index;

    for (entry_index = 0x1F; entry_index >= 0; entry_index--) {
        ((int *)D_800E3648)[entry_index] = 0;
    }
}
