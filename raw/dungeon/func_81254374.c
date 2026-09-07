#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} S32Global;

typedef struct {
    u16 value;
    u16 pad[4];
} U16Global;

extern S32Global D_800E296C;
extern U16Global D_80013714;

extern void func_800A69E4(void);
extern void func_8009FAC4(void);

void func_81254374(void) {
    D_800E296C.value = (s32)(D_800E296C.value & 0xEFFFFFFF);
    func_800A69E4();
    D_80013714.value = (s16)(D_80013714.value & 0xFFF6);
    func_8009FAC4();
}

/* MECHANISM: Preserve the natural 0x18 frame and direct hi/lo global RMWs.
   The first callee is zero-argument; $a0 only holds the RMW mask incidentally.
   Removing the false argument collapses duplicate lui/ori and restores retail scheduling. */
