#include "common.h"
#include "shared/object_flags.h"

extern void release_null_terminated_entries(void *entries);
extern void scene_load_variant_texture_set(void);

// Set the linked object's flag, process the embedded data, and signal an update.
void close_catalog_and_restore_textures(void *object)
{
    void *linkedObject;

    linkedObject = *(void **)object;
    *(u16 *)((u8 *)linkedObject + 0x1E) =
        (u16)(*(u16 *)((u8 *)linkedObject + 0x1E) | 0x2000);
    release_null_terminated_entries((u8 *)object + 0x5C);
    *(u16 *)((u8 *)object - 2) =
        (u16)(*(u16 *)((u8 *)object - 2) | 0x8000);
    object_flag_block.flags |= 0x8000;
    scene_load_variant_texture_set();
}
