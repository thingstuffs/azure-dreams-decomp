#include "common.h"
#include "shared/object_flags.h"

/* Set bit 15 in the preceding halfword and the global value. */
void mark_object_flags_dirty(unsigned short *data)
{
    data[-1] |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
