#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/scene/removal_counter.h"
#include "engine/util.h"

extern int D_800814A0;

/* Decrement the counter and mark the node when the new count is nonzero. */
void decrement_and_flag_removal_if_nonzero(void *body, NodeRemovalCounter *counter)
{
    u16 *flags = &NODE_HEADER(body)->flags;

    if (--counter->count != 0) {
        *flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
