#include "shared/object_flags.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;


/* Mark completion when the referenced object is flagged or the tracked value is zero. */
void func_800BC388(void *context)
{
    void *object = *(void **)context;
    if ((*(u16 *)((u8 *)object + 0x1E) & 0x8000) || (*(*(s32 **)((u8 *)context + 4)) == 0))
    {
        *(u16 *)((u8 *)context - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
