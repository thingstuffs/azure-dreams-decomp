#include "common.h"
#include "shared/object_node.h"
#include "town/map/object_callback.h"
#include "shared/object_flags.h"
#include "town/map.h"
#include "town/menu.h"


/* Runs callbacks unless the object check triggers status clearing and flag updates. */
void run_callbacks_unless_suppressed(void *object, ObjectPosition *position)
{
    CallbackEntry *entry = map_active_callbacks;
    TownObjectRecord *body = object;
    u8 *status_byte;

    if (classify_object_against_bounds(object, position) != 0) {
        status_byte = body->unk_98;
        if (status_byte != 0) {
            *status_byte = 0;
        }
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    while (entry->callback != 0) {
        entry->callback(entry);
        entry++;
    }
}
