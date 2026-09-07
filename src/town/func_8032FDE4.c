#include "common.h"

extern void func_80019448(void *arg0, s32 arg1);
extern void func_80019484(void *arg0, void *arg1);
extern u8 D_80016108[];

void *func_8001A5E4(s32 arg0)
{
    u8 *page;
    s32 call_arg;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_arg = arg0;
    ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    page = (u8 *)0x80020000;
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    func_80019448(page - 0x3C80, call_arg);
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    func_80019484(page - 0x3C80, D_80016108);
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    return page - 0x3C80;
}
