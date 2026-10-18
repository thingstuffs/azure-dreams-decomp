#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

/* Copy g_dungeon_status.unk_1E into the 32-bit value D_8001362C. */
void save_current_monster_direction(void) {
    *(s32 *)0x8001362C = (s32) g_dungeon_status.unk_1E;
}
