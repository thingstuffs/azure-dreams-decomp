#include "common.h"
extern u8 scene_shared_text_buffer[];

extern void copy_string(u8 *destination, u8 *source);
extern void append_string(u8 *dst, u8 *src);
extern u8 D_80016108[];

/* Prepare and return the shared text buffer using the source and D_80016108. */
void *prepare_shared_text_buffer(s32 source)
{
    u32 call_arg;

    call_arg = source;
    copy_string(scene_shared_text_buffer, call_arg);
    append_string(scene_shared_text_buffer, D_80016108);
    return scene_shared_text_buffer;
}
