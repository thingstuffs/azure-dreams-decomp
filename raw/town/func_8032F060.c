#include "common.h"

extern void func_8001ACE8(s16 arg0);
extern void func_8001AD60(s16 arg0);
extern s32 func_8001ADE0(s16 arg0);

void func_80019860(s16 arg0, s16 arg1, s16 arg2)
{
    register s16 arg1_hold ASM_REG("$16");
    register s16 arg1_copy ASM_REG("$17");
    register s16 arg2_hold ASM_REG("$18");
    register s16 arg0_hold ASM_REG("$19");

    ASM_SCHED_BARRIER();
    arg1_hold = arg1;
    arg2_hold = arg2;
    arg0_hold = arg0;
    arg1_copy = arg1_hold;
    ASM_KEEP(arg1_hold);
    ASM_KEEP(arg1_copy);
    ASM_KEEP(arg2_hold);
    ASM_KEEP(arg0_hold);

    if (func_8001ADE0(arg0) != 0) {
        func_8001ACE8(arg1_hold);
        func_8001ACE8(arg2_hold);
    } else {
        func_8001AD60(arg1_copy);
    }
    func_8001ACE8(arg0_hold);
}
