#include "common.h"

extern u8 D_800814D1[16];
extern u8 D_800814D1_read[16] __asm__("D_800814D1");

#define KEEP_POINTER(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))

/* Returns the difference between adjacent byte indices with wraparound at 32. */
s32 func_8003F270(void)
{
    u8 *index_ptr = &D_800814D1[0];
    u32 current_index = D_800814D1_read[0];

    KEEP_POINTER(index_ptr);

    if (current_index < index_ptr[-1]) {
        current_index += 0x20;
    }

    return current_index - index_ptr[-1];
}
