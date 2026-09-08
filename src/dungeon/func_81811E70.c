#include "common.h"

extern u8 D_800157D2[];

/* GCC 2.7.2 does not accept the read/write constraint in ASM_KEEP. */
#if !defined(NON_MATCHING) && __GNUC__ < 3
#define COPY_INDEX(dst, src) __asm__ __volatile__("" : "=r"(dst) : "0"(src))
#else
#define COPY_INDEX(dst, src) ((dst) = (src))
#endif

s32 func_80026E70(s32 arg0, s32 arg1) {
    s32 count;
    register s32 i ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *p;
    u8 value;

    count = 0;
    COPY_INDEX(i, count);
    p = D_800157D2;
loop:
    value = p[0];
    if (value != 0) {
        if ((value == arg0) && (p[-1] == arg1)) {
            count++;
        }
        i++;
        p += 0x13;
        if (i < 0x40) {
            goto loop;
        }
    }
    return count;
}
