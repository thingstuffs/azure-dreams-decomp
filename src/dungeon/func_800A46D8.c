#include "common.h"

s32 func_800A9E38(void *arg0) {
    if (*(s32 *)(*(void **)((s8 *)arg0 - 0x14)) == 0) {
        return 1;
    }

    {
        s32 temp = *(u8 *)((s8 *)arg0 + 19) - 46;

        return (u32)temp < 2;
    }
}
