#include "common.h"
#include "shared/object_flags.h"

extern void submit_five_paired_entry_values(void *owner);
extern void release_null_terminated_entries(void *entries);

/* Updates two object components and sets the object and global high flags. */
void refresh_object_components_and_high_flag(u8 *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        submit_five_paired_entry_values(object + 0x20);
        release_null_terminated_entries(object + 0x80);
        object_flags = *(u16 *)(object + 0x1E) | 0x8000;
        global_flags = object_flag_block.flags | 0x8000;
        *(u16 *)(object + 0x1E) = object_flags;
        object_flag_block.flags = global_flags;
    }
}
