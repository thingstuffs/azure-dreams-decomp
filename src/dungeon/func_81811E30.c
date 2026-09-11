#include "common.h"

extern u8 D_800157D2;

#ifdef NON_MATCHING
#define COPY_REGISTER(dst, src) ((dst) = (src))
#else
#define COPY_REGISTER(dst, src) __asm__ __volatile__("" : "=r"(dst) : "0"(src))
#endif

/* Count matching entry values, stopping at a zero value or 64 entries. */
s32 func_80026E30(s32 target_value) {
    s32 index;
    s32 count;
    u8 *entry;
    u8 value;

    count = 0;
    do {
        COPY_REGISTER(index, count);
        entry = &D_800157D2;
    } while (0);
loop:
    value = *entry;
    if (value != 0) {
        if (value == target_value) {
            count++;
        }
        index++;
        entry += 0x13;
        if (index < 0x40) {
            goto loop;
        }
    }
    return count;
}
