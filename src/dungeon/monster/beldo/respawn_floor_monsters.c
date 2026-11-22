#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo.h"

extern void spawn_initial_floor_monsters(void);

/*
 * Clears the floor and update flag bits, spawns the initial floor monsters and resets the timed
 * sequence data.
 */
void respawn_floor_monsters(void) {
    dungeon_floor_flags = (s32)(dungeon_floor_flags & 0xEFFFFFFF);
    spawn_initial_floor_monsters();
    system_update_flags = (s16)(system_update_flags & 0xFFF6);
    reset_timed_sequence_data();
}
