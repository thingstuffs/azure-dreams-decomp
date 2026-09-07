#include "common.h"

void func_80026FB4(void *arg0) {
    u8 *ptr = arg0;
    s32 *global;
    u16 flags;
    s32 global_flags;

    global = (s32 *)0x80080000;
    asm volatile("" : "=r"(global) : "0"(global));
    flags = *(u16 *)(ptr + 0x1E);
    global_flags = global[0x528];
    flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)(ptr + 0x1E) = flags;
    global[0x528] = global_flags;
}
