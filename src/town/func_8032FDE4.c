#include "common.h"
extern u8 D_8001C380[];

extern void townCopyString(u8 *destination, u8 *source);
extern void townAppendString(u8 *dst, u8 *src);
extern u8 D_80016108[];

/* Prepare and return the shared text buffer using the source and D_80016108. */
void *townPrepareSharedTextBuffer(s32 source)
{
    u32 call_arg;

    call_arg = source;
    townCopyString(D_8001C380, call_arg);
    townAppendString(D_8001C380, D_80016108);
    return D_8001C380;
}
