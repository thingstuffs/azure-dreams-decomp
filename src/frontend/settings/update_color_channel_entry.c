#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

/* Load an indexed value divided by four and propagate the source flag. */
void update_color_channel_entry(void *entry_data) {
    MainTitleValueEntry *entry = entry_data;
    u8 *value_data = entry->value_data;
    s32 value_index = entry->value_index;
    s16 scaled_value;

    scaled_value = (s16)(*(u16 *)(value_data + (value_index * 2) + 0xE) << 0x10 >> 0x12);
    entry->value = scaled_value;
    if (*(s16 *)(value_data + 0x16) & 0x8000) {
        ((ObjectNodeHeader *)entry - 1)->flags = ((ObjectNodeHeader *)entry - 1)->flags | NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
