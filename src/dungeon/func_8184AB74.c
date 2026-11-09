/* Relink of matched town/func_800C19FC; every changed retail word is a paired relocation. */
#include "common.h"
#include "slus/imports.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


// Process the source and set destination and global flags when source status bits are set.
void advance_counter_and_propagate_target_flags(void *destination, s32 unused, void *source)
{
    advance_sprite_animation_and_textures(source);
    if (*(u16 *)((u8 *)source + 0x14) & 0x6000) {
        NODE_HEADER(destination)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
