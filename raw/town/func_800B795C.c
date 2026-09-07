#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_8004B248(void *a0);
extern void func_8004B1A4(void *a0);
extern void func_800B5020(void *a0);
extern s32 D_800814A0;

void func_800B50BC(u8 *arg0)
{
    u8 *temp_s0;
    u16 flags;
    s32 glob;

    if (arg0 != NULL) {
        temp_s0 = arg0 + 0x20;
        func_8004B248(arg0 + 0x80);
        func_8004B1A4(*(void **)(temp_s0 + 0x20));
        func_800B5020(*(void **)(temp_s0 + 0x5C));
        flags = *(u16 *)(arg0 + 0x1E) | 0x8000;
        glob = D_800814A0 | 0x8000;
        *(u16 *)(arg0 + 0x1E) = flags;
        D_800814A0 = glob;
    }
}
