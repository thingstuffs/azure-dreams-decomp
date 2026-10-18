#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern void spawn_initial_floor_monsters(void);
extern void set_monster_data_pointer(void);

/* Clears global flag bits and calls spawn_initial_floor_monsters and set_monster_data_pointer. */
void clear_global_effect_flags(void) {
    D_800E296C = (s32)(D_800E296C & 0xEFFFFFFF);
    spawn_initial_floor_monsters();
    D_80013714 = (s16)(D_80013714 & 0xFFF6);
    set_monster_data_pointer();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
