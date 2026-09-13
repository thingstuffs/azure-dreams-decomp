#include "common.h"

extern void func_80019448(void *arg0, s32 arg1);
extern void func_80019484(void *arg0, void *arg1);
extern u8 D_80016108[];

/* Prepare and return the shared text buffer using the source and D_80016108. */
void *func_8001A5E4(s32 source)
{
    u8 *page;
    u32 call_arg;

    call_arg = source;
    page = (u8 *)0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_80019448(page - 0x3C80, call_arg);
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    func_80019484(page - 0x3C80, D_80016108);
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    return page - 0x3C80;
}
