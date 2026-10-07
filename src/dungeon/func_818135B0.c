#include "common.h"
#include "shared/object_flags.h"

extern void func_80028534(void *state);
extern void func_8004B1A4(void *object);
extern void func_8004B248(void *entries);

// Updates linked and embedded object data, then sets the object and global 0x8000 flags.
void func_800285B0(void *object)
{
    u8 *objectData;
    u16 objectFlags;
    s32 globalFlags;

    if (object != 0) {
        objectData = (u8 *)object + 0x20;
        func_80028534(*(void **)(objectData + 0x88));
        func_8004B1A4(*(void **)(objectData + 0x40));
        func_8004B248((u8 *)object + 0xAC);
        objectFlags = *(u16 *)((u8 *)object + 0x1E);
        globalFlags = objectFlagBlock.flags;
        *(u16 *)((u8 *)object + 0x1E) = objectFlags | 0x8000;
        objectFlagBlock.flags = globalFlags | 0x8000;
    }
}
