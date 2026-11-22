#include "common.h"
#include "engine/item.h"
#include "engine/util.h"

/* Check the watched value and then decrement the same node counter. */
void mark_and_release_record_pair(void *body, struct NodeRemovalCounter *counter)
{
    flag_removal_when_value_zero(body, counter);
    decrement_and_flag_removal_if_nonzero(body, counter);
}
