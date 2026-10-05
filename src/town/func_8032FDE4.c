#include "common.h"
extern u8 D_8001C380[];

extern void func_80019448(u8 *destination, u8 *source);
extern void func_80019484(u8 *dst, u8 *src);
extern u8 D_80016108[];

/* Prepare and return the shared text buffer using the source and D_80016108. */
void *func_8001A5E4(s32 source)
{
    u32 call_arg;

    call_arg = source;
    func_80019448(D_8001C380, call_arg);
    func_80019484(D_8001C380, D_80016108);
    return D_8001C380;
}
