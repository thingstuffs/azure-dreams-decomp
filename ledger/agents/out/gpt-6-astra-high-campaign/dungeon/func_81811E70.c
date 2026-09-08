#include "common.h"

extern u8 D_800157D2[];

/* GCC 2.7.2 does not accept the read/write constraint in ASM_KEEP. */
#if !defined(NON_MATCHING) && __GNUC__ < 3
#define COPY_INDEX(dst, src) __asm__ __volatile__("" : "=r"(dst) : "0"(src))
#else
#define COPY_INDEX(dst, src) ((dst) = (src))
#endif

/* Count entries matching both bytes, stopping at a zero value or 64 entries. */
s32 func_80026E70(s32 target_value, s32 prefix_value) {
    s32 count;
    register s32 index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *entry;
    u8 value;

    count = 0;
    COPY_INDEX(index, count);
    entry = D_800157D2;
loop:
    value = entry[0];
    if (value != 0) {
        if ((value == target_value) && (entry[-1] == prefix_value)) {
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
