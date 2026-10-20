#include "common.h"

extern s32 create_callback_pair_default(s32 a0);
extern void release_null_terminated_entries(s32 *a0);

/* Fills the array with allocated buffers, flagging prior allocations and returning NULL on failure. */
s32 *alloc_buffer_array(s32 *buffers, s32 buffer_count)
{
    s32 index;
    s32 buffer;

    for (index = 0; index < buffer_count; index++) {
        buffer = create_callback_pair_default(0x82);
        buffers[index] = buffer;
        if (buffer == 0) {
            release_null_terminated_entries(buffers);
            buffers = 0;
            break;
        }
    }
    return buffers;
}
