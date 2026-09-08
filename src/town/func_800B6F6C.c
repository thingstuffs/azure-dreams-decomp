#include "common.h"

extern void func_800B4648(void *arg0);
extern void func_8004B248(void *arg0);
extern s32 D_800814A0[];

/* Updates two object components and sets the object and global high flags. */
void func_800B46CC(u8 *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        func_800B4648(object + 0x20);
        func_8004B248(object + 0x80);
        object_flags = *(u16 *)(object + 0x1E) | 0x8000;
        global_flags = D_800814A0[0] | 0x8000;
        *(u16 *)(object + 0x1E) = object_flags;
        D_800814A0[0] = global_flags;
    }
}
