#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

extern Counter D_80026472;

/* Increment the object and global counters and flag the object after 256 counts. */
void func_8188CFAC(u16 *object)
{
    u16 object_count;
    s32 counter;

    counter = D_80026472.value;
    object_count = object[13] + 1;
    counter++;
    object[13] = object_count;
    D_80026472.value = counter;
    if ((s16)object_count >= 0x101) {
        object[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
