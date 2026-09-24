#include "common.h"

typedef struct S_func_80026F04_0 {
    u8 pad_00[0x57D2];
    u8 unk_57D2;
} S_func_80026F04_0;

/* Find the first matching entry at or after the starting index, or return -1. */
s32 func_80026F04(s32 target_value, s32 start_index)
{
    s32 index;

    for (index = start_index; index < 0x40; index++) {
        if (((S_func_80026F04_0 *)((u8 *)0x80010000 + index * 19))->unk_57D2 == target_value) {
            return index;
        }
    }
    return -1;
}
