#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "frontend/settings.h"


/* Packs three capped source components, copies an attribute, and propagates the high-bit flag. */
void update_packed_color_entry(MainTitleValueEntry *destination) {
    MainTitleValueEntry *dest = destination;
    SettingsScreenBody *source;
    s32 component;
    s32 byte_index;
    s32 shift;
    s32 packed_value;

    source = dest->owner;
    byte_index = 2;
    dest->color = 0;
    do {
        component = source->color_channels[byte_index];
        if (component >= 0x100) {
            component = 0xFF;
        }
        shift = byte_index * 8;
        byte_index -= 1;
        packed_value = dest->color;
        packed_value = packed_value + (component << shift);
        dest->color = packed_value;
    } while (byte_index >= 0);
    dest->style = source->shade;
    if ((s16)source->flags & NODE_REMOVE) {
        NODE_HEADER(dest)->flags = NODE_HEADER(dest)->flags | NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
