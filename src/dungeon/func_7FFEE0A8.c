#include "modules/dungeon_town_map.h"

s32 clear_town_map_status(void) {
    D_800FC418 = 0;
    return 1;
}
