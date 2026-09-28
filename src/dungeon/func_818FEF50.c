#include "common.h"
#include "shared/object_flags.h"

extern s16 D_80025E80;

/* Sets the object and global flags and marks the update. */
void func_818FEF50(void *object) {
    u16 *flags = (u16 *)object - 1;

    D_80025E80 = 1;
    *flags |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
