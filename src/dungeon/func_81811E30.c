#include "common.h"

extern u8 D_800157D2;

#ifdef NON_MATCHING
#define COPY_REGISTER(dst, src) ((dst) = (src))
#else
#define COPY_REGISTER(dst, src) __asm__ __volatile__("" : "=r"(dst) : "0"(src))
#endif

s32 func_80026E30(s32 arg0) {
    s32 index;
    register s32 count ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *entry;
    u8 value;

    count = 0;
    COPY_REGISTER(index, count);
    entry = &D_800157D2;
loop:
    value = *entry;
    if (value != 0) {
        if (value == arg0) {
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
