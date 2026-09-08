#include "common.h"

extern s32 func_8004B404(s32 a0);
extern void func_8004B248(s32 *a0);

/* Fills the array with allocated buffers, flagging prior allocations and returning NULL on failure. */
s32 *allocBufferArray(s32 *buffer_array, s32 buffer_count)
{
    s32 *buffers = buffer_array;
    s32 count = buffer_count;
    s32 index;
    s32 buffer;

    for (index = 0; index < count; index++)
    {
        buffer = func_8004B404(0x82);
        buffers[index] = buffer;
        if (buffer == 0)
        {
            func_8004B248(buffers);
            buffers = 0;
            break;
        }
    }
    return buffers;
}
