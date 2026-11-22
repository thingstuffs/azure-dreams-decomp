#include "frontend/settings.h"
#include "frontend/settings/owner_linked_body.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

/* Remove this record node once its owner is marked for removal. */
void remove_record_with_marked_owner(SettingsOwnerLinkedBody *body) {
    if ((s16)body->owner->flags & NODE_REMOVE) {
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
