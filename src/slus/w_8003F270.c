#include "common.h"

extern u8 D_800814D1;

/* Returns the difference between adjacent byte indices with wraparound at 32. */
s32 func_8003F270(void)
{
    u8 *index_ptr = &D_800814D1;
    u32 current_index = D_800814D1;

    if (index_ptr[0] < index_ptr[-1]) {
        current_index += 0x20;
    }

    return current_index - index_ptr[-1];
}
