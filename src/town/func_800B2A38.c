#include "common.h"

extern s32 *realloc_field_0_buffer(s32 *buffer_slot, s32 entry_count, s32 clear_words);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(void *entries, s32 value, s32 count);

extern s32 display_vector_defaults[];


/* Allocates actor display entries, shares a default vector across 40 entries, and reports success. */
s32 load_actor_display_resource(void *object, s32 entry_count) {
    s32 success = 0;
    s32 *handle = realloc_field_0_buffer((s32 *)((u8 *)object + 0xAC), entry_count, 12);

    *(s32 **)((u8 *)object + 0xA8) = handle;
    if (handle != 0) {
        *(s32 *)((u8 *)object + 0x8C) = display_vector_defaults[0];
        *(s32 *)((u8 *)object + 0x90) = display_vector_defaults[1];
        *(s32 *)((u8 *)object + 0x94) = display_vector_defaults[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, (s32)((u8 *)object + 0x8C), 40);
        success = 1;
    }
    return success;
}
