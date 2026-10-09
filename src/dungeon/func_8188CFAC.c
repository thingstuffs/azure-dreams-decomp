#include "modules/dungeon_ovl_18ac800.h"
#include "common.h"
#include "shared/object_flags.h"


/* Increment the object and global counters and flag the object after 256 counts. */
void func_800247AC(u16 *object)
{
    u16 object_count;
    s32 counter;

    counter = D_80026472.value.u;
    object_count = object[13] + 1;
    counter++;
    object[13] = object_count;
    D_80026472.value.u = counter;
    if ((s16)object_count >= 0x101) {
        object[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
