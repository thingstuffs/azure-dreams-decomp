#include "common.h"

extern s32 func_80049004(s32 *a0, s32 a1, s32 a2);
extern s32 texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 a0, void *a1, s32 a2);
extern s32 display_vector_defaults[];

/* Initializes the object handle and applies the default configuration on success. */
s32 load_item_menu_display_resource(void *object, s32 resource_id) {
    s32 success = 0;
    s32 handle = func_80049004((s32 *)((s8 *)object + 0xDC), resource_id, 8);

    *(s32 *)((s8 *)object + 0xD8) = handle;
    if (handle != 0) {
        *(s32 *)((s8 *)object + 0xBC) = display_vector_defaults[0];
        *(s32 *)((s8 *)object + 0xC0) = display_vector_defaults[1];
        *(s32 *)((s8 *)object + 0xC4) = display_vector_defaults[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, (s8 *)object + 0xBC, 0x1A);
        success = 1;
    }
    return success;
}
