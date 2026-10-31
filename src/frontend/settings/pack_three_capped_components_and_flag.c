#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"


/* Packs three capped source components, copies an attribute, and propagates the high-bit flag. */
void pack_three_capped_components_and_flag(void *destination) {
    MainTitleValueEntry *dest = destination;
    void *source;
    void *component_cursor;
    s32 component;
    s32 byte_index;
    s32 shift;
    s32 packed_value;

    source = dest->value_data;
    byte_index = 2;
    dest->packed_components = 0;
    component_cursor = (s8 *) source + 4;
    do {
        component = *(s16 *) ((s8 *) component_cursor + 0xE);
        if (component >= 0x100) {
            component = 0xFF;
        }
        component_cursor = (s8 *) component_cursor - 2;
        shift = byte_index * 8;
        byte_index -= 1;
        packed_value = dest->packed_components;
        packed_value = packed_value + (component << shift);
        dest->packed_components = packed_value;
    } while (byte_index >= 0);
    dest->attribute = *(u16 *) ((s8 *) source + 0x14);
    if (*(s16 *) ((s8 *) source + 0x16) & 0x8000) {
        *(u16 *) ((s8 *) dest - 2) = *(u16 *) ((s8 *) dest - 2) | NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
