#include "common.h"
#include "shared/object_flags.h"

extern void func_8004B1A4(s32 arg0);
extern s32 D_800E5910[];

/* Process the object handle, clear the global state, and set the high flag bits. */
void func_800DCE0C(void *object)
{
    func_8004B1A4(*(s32 *)((u8 *)object + 0x5C));
    D_800E5910[0] = 0;
    {
        u16 object_flags = *(u16 *)((u8 *)object + 0x1E);
        s32 global_flags = objectFlagBlock.flags;
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        objectFlagBlock.flags = global_flags | 0x8000;
    }
}
