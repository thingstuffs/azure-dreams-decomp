#include "common.h"
#include "shared/object_flags.h"

/* Sets bit 0x8000 in the object and global flags when the object exists. */
void func_8004EE90(unsigned short *object_fields)
{
    if (object_fields != 0) {
        u16 flags = object_fields[0xF];
        int global_flags = objectFlagBlock.flags;
        object_fields[0xF] = flags | 0x8000;
        objectFlagBlock.flags = global_flags | 0x8000;
    }
}
