#include "town/menu.h"
#include "shared/gpu_packets.h"

typedef struct MenuResourceOwner {
    u8 pad_00[0xB0];
    DisplayPositionWords vector;
    u8 pad_BC[0x10];
    s32 handle;
    s32 buffer;
} MenuResourceOwner;

extern s32 realloc_field_0_buffer(s32 *, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32, void *, s32);
extern DisplayPositionWords display_vector_defaults;

/* Allocate the menu's twelve-entry buffer and link its display vector. */
s32 load_menu_display_resource(MenuResourceOwner *owner, s32 resource)
{
    s32 success = 0;
    s32 handle = realloc_field_0_buffer(&owner->buffer, resource, 12);

    owner->handle = handle;
    if (handle != 0) {
        owner->vector.unk0 = display_vector_defaults.unk0;
        owner->vector.unk4 = display_vector_defaults.unk4;
        owner->vector.unk8 = display_vector_defaults.unk8;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, &owner->vector, 31);
        success = 1;
    }
    return success;
}
