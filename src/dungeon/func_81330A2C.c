/* Relink of matched town/func_800C19FC; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *source);

// Process the source and set destination and global flags when source status bits are set.
void func_80167A2C(void *destination, s32 unused, void *source)
{
    advance_sprite_animation_and_textures(source);
    if (*(u16 *)((u8 *)source + 0x14) & 0x6000) {
        *(u16 *)((u8 *)destination - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
