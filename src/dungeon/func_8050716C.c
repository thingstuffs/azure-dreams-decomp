/* Relink of matched dungeon/func_8028B96C; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_spawns.h"

void func_8001E96C(void) {
    s32 entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        ((int *)D_800E3548)[entry_index] = 0;
    }
}
