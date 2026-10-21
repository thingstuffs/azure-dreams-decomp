#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern void spawn_initial_floor_monsters(void);
extern void set_monster_data_pointer(void);

/* Clears global flag bits and calls spawn_initial_floor_monsters and set_monster_data_pointer. */
void clear_global_effect_flags(void) {
    dungeon_floor_flags = (s32)(dungeon_floor_flags & 0xEFFFFFFF);
    spawn_initial_floor_monsters();
    system_update_flags = (s16)(system_update_flags & 0xFFF6);
    set_monster_data_pointer();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
