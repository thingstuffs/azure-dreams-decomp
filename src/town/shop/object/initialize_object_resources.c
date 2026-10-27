#include "common.h"
#include "engine/resource.h"

extern s32 func_80049004();
extern s32 texture_set_the_field_offset_hex_8_in_each_entry_pointer_array();
extern s32 display_vector_defaults[];

/* Initializes object resources and defaults, returning whether the auxiliary allocation succeeds. */
s32 initialize_object_resources(void *object, s32 resource_id) {
    s32 *default_values;
    void *buffer;
    s32 success = 0;

    if ((*(s32 *)((s8 *)object + 0x5C) = func_80049004((s8 *)object + 0x60, resource_id, 0xC)) != 0) {
        default_values = display_vector_defaults;
        *(s32 *)((s8 *)object + 0x40) = display_vector_defaults[0];
        *(s32 *)((s8 *)object + 0x44) = default_values[1];
        *(s32 *)((s8 *)object + 0x48) = default_values[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(*(s32 *)((s8 *)object + 0x5C), (s8 *)object + 0x40, 0x29);
        buffer = create_callback_pair_default(0x48);
        success = buffer != 0;
        *(void **)((s8 *)object + 0x20) = buffer;
    }
    return success;
}
