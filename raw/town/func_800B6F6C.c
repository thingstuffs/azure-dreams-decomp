#include "common.h"

extern void func_800B4648(void *arg0);
extern void func_8004B248(void *arg0);
extern s32 D_800814A0[];

void func_800B46CC(u8 *arg0)
{
    u16 flags;
    s32 glob;

    if (arg0 != 0) {
        func_800B4648(arg0 + 0x20);
        func_8004B248(arg0 + 0x80);
        flags = *(u16 *)(arg0 + 0x1E) | 0x8000;
        glob = D_800814A0[0] | 0x8000;
        *(u16 *)(arg0 + 0x1E) = flags;
        D_800814A0[0] = glob;
    }
}
