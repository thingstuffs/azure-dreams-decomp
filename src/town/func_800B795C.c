#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_8004B248(void *a0);
extern void func_8004B1A4(void *a0);
extern void func_800B5020(void *a0);
extern s32 D_800814A0;

// Process an object's associated resources and set its and the global high-bit flags.
void func_800B50BC(u8 *object)
{
    u8 *resourceFields;
    u16 objectFlags;
    s32 globalFlags;

    if (object != NULL) {
        resourceFields = object + 0x20;
        func_8004B248(object + 0x80);
        func_8004B1A4(*(void **)(resourceFields + 0x20));
        func_800B5020(*(void **)(resourceFields + 0x5C));
        objectFlags = *(u16 *)(object + 0x1E) | 0x8000;
        globalFlags = D_800814A0 | 0x8000;
        *(u16 *)(object + 0x1E) = objectFlags;
        D_800814A0 = globalFlags;
    }
}
