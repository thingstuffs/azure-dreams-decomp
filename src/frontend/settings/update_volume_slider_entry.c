#include "modules/main_title_callbacks.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "frontend/settings.h"

extern s32 volume_slider_levels[];

/* Load a table value divided by four and propagate the source flag. */
void update_volume_slider_entry(MainTitleValueEntry *entry)
{
    entry->width = (s16)(volume_slider_levels[entry->index] >> 2);
    if ((s16)entry->owner->flags & NODE_REMOVE) {
        NODE_HEADER(entry)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
