#include "modules/dungeon_town_map.h"

s32 town_map_del(void) {
    D_800FC418 = 0xFF;
    return 1;
}
