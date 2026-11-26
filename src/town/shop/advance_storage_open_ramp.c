#include "town/person/four_slot_object_owner_g00628.h"
#include "shared/object_node.h"

void advance_storage_open_ramp(StorageMenuObject *object)
{
    s32 next_step;

    object->links.display->ramp = (object->open_step << 12) / 5;
    next_step = object->open_step + 1;
    object->open_step = next_step;
    if (next_step >= 6) {
        NODE_HEADER(object)->update_callback = update_storage_cursor_and_fade_indicators;
    }
}
