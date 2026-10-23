#include "common.h"
#include "shared/dungeon_floor.h"


/* Sets bit 0x40 in dungeon_floor_flags. */
void set_boss_effect_flag(void) {
    dungeon_floor_flags = (s32)(dungeon_floor_flags | 0x40);
}
