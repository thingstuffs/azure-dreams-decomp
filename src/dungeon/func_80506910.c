/* Relink of matched dungeon/func_8028B110; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_spawns.h"

s32 isFloorItemTileOccupied(s32 excluded_slot, s16 x, s16 y)
{
    s32 slot;

    for (slot = 0; slot < 64; slot++) {
        if ((excluded_slot != slot) &&
            (D_800E3548[slot].kind != 0) &&
            (((floor_spawns_isolated_8028B110_DungeonPosition *)D_800E36C8)[slot].x == x) &&
            (((floor_spawns_isolated_8028B110_DungeonPosition *)D_800E36C8)[slot].y == y)) {
            return 1;
        }
    }
    return 0;
}
