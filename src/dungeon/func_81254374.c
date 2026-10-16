#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern void spawnInitialFloorMonsters(void);
extern void dungeonSetMonsterDataPointer(void);

/* Clears global flag bits and calls spawnInitialFloorMonsters and dungeonSetMonsterDataPointer. */
void dungeonClearGlobalEffectFlags(void) {
    D_800E296C = (s32)(D_800E296C & 0xEFFFFFFF);
    spawnInitialFloorMonsters();
    D_80013714 = (s16)(D_80013714 & 0xFFF6);
    dungeonSetMonsterDataPointer();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
