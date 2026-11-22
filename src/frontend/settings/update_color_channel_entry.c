#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

/* Load an indexed value divided by four and propagate the source flag. */
void update_color_channel_entry(MainTitleValueEntry *entry_data) {
    MainTitleValueEntry *entry = entry_data;
    SettingsScreenBody *owner = entry->owner;
    s32 value_index = entry->index;
    s16 scaled_value;

    scaled_value = (s16)(owner->color_channels[value_index] >> 2);
    entry->width = scaled_value;
    if ((s16)owner->flags & NODE_REMOVE) {
        NODE_HEADER(entry)->flags = NODE_HEADER(entry)->flags | NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
