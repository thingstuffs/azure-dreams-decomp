#include "common.h"
#include "shared/object_flags.h"

extern void func_80026250(void *context);
extern void func_8004B248(u16 **entries);

/* Process the object resources and set the object and global flags. */
void func_80026294(void *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        func_80026250(*(void **)((u8 *)object + 0x74));
        func_8004B248((u16 **)((u8 *)object + 0x78));
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = objectFlagBlock.flags;
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        objectFlagBlock.flags = global_flags | 0x8000;
    }
}
