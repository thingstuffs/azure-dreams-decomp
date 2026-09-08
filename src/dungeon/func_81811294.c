#include "common.h"

extern void func_80026250(void *arg0);
extern void func_8004B248(u16 **arg0);
extern s32 D_800814A0[3];

/* Process the object resources and set the object and global flags. */
void func_80026294(void *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        func_80026250(*(void **)((u8 *)object + 0x74));
        func_8004B248((u16 **)((u8 *)object + 0x78));
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = D_800814A0[0];
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        D_800814A0[0] = global_flags | 0x8000;
    }
}
