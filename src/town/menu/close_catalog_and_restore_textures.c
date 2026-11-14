#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/graphics.h"
#include "engine/item.h"
#include "town/menu.h"

// Set the linked object's flag, process the embedded data, and signal an update.
void close_catalog_and_restore_textures(void *object)
{
    void *linkedObject;

    linkedObject = *(void **)object;
    *(u16 *)((u8 *)linkedObject + 0x1E) =
        (u16)(*(u16 *)((u8 *)linkedObject + 0x1E) | 0x2000);
    release_null_terminated_entries((u8 *)object + 0x5C);
    NODE_HEADER(object)->flags =
        (u16)(NODE_HEADER(object)->flags | NODE_REMOVE);
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    load_variant_texture_set();
}
