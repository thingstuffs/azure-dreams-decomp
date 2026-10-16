#include "modules/town_ovl_3ef1c8.h"

void func_80017D24(void)
{
    void *choices[2] = { &D_8001AB94, &D_8001ABE8 };
    void *town = *(void **)((s8 *)*(void **)((s8 *)(&D_80016000)) + 0x40);

    townInvokeAlternateHandlerWithCode780();
    townInvokeHandlerWithCode79E();
    if (func_8001A510(D_8001A91E) == 0) {
        func_8001A490(0x7A3);
    }
    D_8001B320 = choices[*(s32 *)((s8 *)town + 0xB0)];
}

/* MECHANISM: Two sibling pointer locals create the retail sp+0x10/sp+0x14 table
   while the town pointer alone remains live in s0 across calls.  An entry
   scheduling fence keeps the ra/s0 saves ahead of independent table setup. */
