#include "common.h"
#include "shared/object_flags.h"
#include "frontend/card.h"

/* Set bit 15 in the preceding halfword and the global value. */
void mark_node_for_removal(unsigned short *data)
{
    data[-1] |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
