/* Relink of matched dungeon/func_81087200; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/object_flags.h"

extern void func_800478B8(void *source);

// Process the source and set destination and global flags when source status bits are set.
void func_80150A00(void *destination, s32 unused, void *source)
{
    func_800478B8(source);
    if (*(u16 *)((u8 *)source + 0x14) & 0x6000) {
        *(u16 *)((u8 *)destination - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
