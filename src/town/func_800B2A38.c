#include "common.h"
#include "shared/item_menu.h"

extern void *realloc_field_0_buffer(void *buffer_slot, s32 entry_count, s32 clear_words);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(ItemMenuPart **entries, DisplayPositionWords *value, s32 count);

extern s32 display_vector_defaults[];


/* Allocates actor display entries, shares a default vector across 40 entries, and reports success. */
s32 load_actor_display_resource(ItemMenuObject *object, s32 entry_count) {
    s32 success = 0;
    ItemMenuPart **parts = realloc_field_0_buffer(object->allocations, entry_count, 12);

    object->parts = parts;
    if (parts != 0) {
        object->part_vector.unk0 = display_vector_defaults[0];
        object->part_vector.unk4 = display_vector_defaults[1];
        object->part_vector.unk8 = display_vector_defaults[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(parts, &object->part_vector, 40);
        success = 1;
    }
    return success;
}
