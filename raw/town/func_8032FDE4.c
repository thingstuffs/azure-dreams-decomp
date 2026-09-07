#include "common.h"

extern void func_80019448(void *arg0, s32 arg1);
extern void func_80019484(void *arg0, void *arg1);
extern u8 D_80016108[];

void *func_8001A5E4(s32 arg0)
{
    register u8 *page ASM_REG("$16");
    register s32 call_arg ASM_REG("$5");

    ASM_SCHED_BARRIER();
    call_arg = arg0;
    ASM_KEEP(call_arg);
    page = (u8 *)0x80020000;
    ASM_KEEP(page);
    func_80019448(page - 0x3C80, call_arg);
    ASM_KEEP(page);
    func_80019484(page - 0x3C80, D_80016108);
    ASM_KEEP(page);
    return page - 0x3C80;
}
