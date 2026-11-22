#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/scene/removal_counter.h"
#include "engine/util.h"

extern int D_800814A0;

/* Mark the node for removal when the watched value is zero. */
void flag_removal_when_value_zero(void *body, NodeRemovalCounter *counter) {
    u16 *flags = &NODE_HEADER(body)->flags;

    if (*counter->watched_value == 0) {
        *flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
