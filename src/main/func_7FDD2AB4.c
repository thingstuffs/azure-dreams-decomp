#include "common.h"
#include "shared/object_flags.h"

/* Set bit 15 in the preceding halfword and the global value. */
void func_7FDD2AB4(unsigned short *data)
{
    data[-1] |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
