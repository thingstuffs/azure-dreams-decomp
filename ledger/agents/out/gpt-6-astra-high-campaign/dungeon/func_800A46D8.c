#include "common.h"

/* Checks whether the linked word is zero or the record byte is 46 or 47. */
s32 func_800A9E38(void *record) {
    if (*(s32 *)(*(void **)((s8 *)record - 0x14)) == 0) {
        return 1;
    }

    {
        s32 value_offset = *(u8 *)((s8 *)record + 19) - 46;

        return (u32)value_offset < 2;
    }
}
