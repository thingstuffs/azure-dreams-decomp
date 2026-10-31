#include "modules/main_title_callbacks.h"
#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

extern s32 volume_slider_levels[];

/* Load a table value divided by four and propagate the source flag. */
void load_table(MainTitleValueEntry *entry)
{
    entry->value = (s16)(volume_slider_levels[entry->value_index] >> 2);
    if (*(short *)((char *)entry->value_data + 0x16) & 0x8000) {
        *(unsigned short *)((char *)entry - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
