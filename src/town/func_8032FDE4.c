#include "common.h"
extern u8 D_8001C380[];

extern void copy_string(u8 *destination, u8 *source);
extern void append_string(u8 *dst, u8 *src);
extern u8 D_80016108[];

/* Prepare and return the shared text buffer using the source and D_80016108. */
void *prepare_shared_text_buffer(s32 source)
{
    u32 call_arg;

    call_arg = source;
    copy_string(D_8001C380, call_arg);
    append_string(D_8001C380, D_80016108);
    return D_8001C380;
}
