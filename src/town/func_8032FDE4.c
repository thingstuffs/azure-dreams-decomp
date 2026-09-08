#include "common.h"

extern void func_80019448(void *arg0, s32 arg1);
extern void func_80019484(void *arg0, void *arg1);
extern u8 D_80016108[];

void *func_8001A5E4(s32 arg0)
{
    u8 *page;
    s32 call_arg;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_arg = arg0;
    ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    page = (u8 *)0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_80019448(page - 0x3C80, call_arg);
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_80019484(page - 0x3C80, D_80016108);
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    return page - 0x3C80;
}
