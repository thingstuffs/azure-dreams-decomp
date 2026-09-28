#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"

extern void func_800A69E4(void);
extern void func_8009FAC4(void);

/* Clears global flag bits and calls func_800A69E4 and func_8009FAC4. */
void func_81254374(void) {
    D_800E296C = (s32)(D_800E296C & 0xEFFFFFFF);
    func_800A69E4();
    D_80013714 = (s16)(D_80013714 & 0xFFF6);
    func_8009FAC4();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
