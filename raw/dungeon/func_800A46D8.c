#include "common.h"

extern s32 func_800A9E68(void *arg0);

s32 func_800A9E38(void *arg0) {
    if (*(s32 *)(*(void **)((s8 *)arg0 - 0x14)) == 0) {
        __asm__ __volatile__("" ::: "memory");
        return 1;
    }

    {
        s32 temp = *(u8 *)((s8 *)arg0 + 19) - 46;

        __asm__ __volatile__("" : : "r"(temp));
        return (u32)func_800A9E68(arg0) < 2;
    }
}
