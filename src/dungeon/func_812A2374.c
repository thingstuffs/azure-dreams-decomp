#define set_monster_data_pointer func_8009E8B4
#define spawn_initial_floor_monsters func_800A569C
#define D_800E296C D_800E1D4C
/* Relink of matched dungeon/clear_global_effect_flags at file 0x1274374; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern void func_800A569C(void);
extern void func_8009E8B4(void);

/* Clears global flag bits and calls func_800A569C and func_8009E8B4. */
void func_8014EB74(void) {
    D_800E1D4C = (s32)(D_800E1D4C & 0xEFFFFFFF);
    func_800A569C();
    D_80013714 = (s16)(D_80013714 & 0xFFF6);
    func_8009E8B4();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
