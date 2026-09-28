#include "common.h"
#include "shared/object_flags.h"

/* --- gcc 2.95.2 -O2 -fstrict-aliasing TU --- */

/* Sets the "used"/flag bit (0x8000) on a 16-bit field at offset 0x1E within
 * *a0, and on the global flags word D_800814A0, but only if a0 is non-NULL. */
/* Sets bit 0x8000 in the object and global flags when the object exists. */
void func_8004EE90(unsigned short *object_fields)
{
    if (object_fields != 0) {
        object_fields[0xF] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
