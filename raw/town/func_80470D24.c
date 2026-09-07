#include "common.h"

extern void func_80017C64(void);
extern void func_80017D04(void);
extern void func_8001A490(s32);
extern s32 func_8001A510(s32);

extern s8 D_80016000[];
extern s16 D_8001A91E;
extern s32 D_8001AB94;
extern s32 D_8001ABE8;
extern s32 D_8001B320;

void func_80017D24(void)
{
    void *choices[2];
    void *town;

    ASM_SCHED_BARRIER();
    choices[0] = &D_8001AB94;
    choices[1] = &D_8001ABE8;
    town = *(void **)((s8 *)*(void **)D_80016000 + 0x40);
    func_80017C64();
    func_80017D04();
    if (func_8001A510(D_8001A91E) == 0) {
        func_8001A490(0x7A3);
    }
    D_8001B320 = choices[*(s32 *)((s8 *)town + 0xB0)];
}

/* MECHANISM: Two sibling pointer locals create the retail sp+0x10/sp+0x14 table
   while the town pointer alone remains live in s0 across calls.  An entry
   scheduling fence keeps the ra/s0 saves ahead of independent table setup. */
