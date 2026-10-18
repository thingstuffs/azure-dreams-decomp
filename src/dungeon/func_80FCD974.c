/* Relink of matched town/func_800C19FC; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/object_flags.h"

extern void func_800478B8(void *source);

// Process the source and set destination and global flags when source status bits are set.
void func_8015D174(void *destination, s32 unused, void *source)
{
    func_800478B8(source);
    if (*(u16 *)((u8 *)source + 0x14) & 0x6000) {
        *(u16 *)((u8 *)destination - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
