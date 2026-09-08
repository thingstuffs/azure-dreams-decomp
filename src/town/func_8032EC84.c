#include "common.h"

/* Append the source string to the destination and return the destination start. */
u8 *func_80019484(u8 *dst, volatile u8 *src) {
    u8 *dst_start = dst;

    if (*dst_start == 0) {
        goto check_src;
    }
    do {
        dst++;
    } while (*dst != 0);
    goto check_src;
copy_byte:
    *dst = *src;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    dst++;
    src++;
check_src:
    if (*src != 0) {
        goto copy_byte;
    }
    *dst = 0;
    return dst_start;
}

/* MECHANISM: Frameless leaf: ret holds the original destination in v1.
   A do-scan plus explicit body/check labels preserves retail's bottom tests.
   Volatile src reloads each byte; a post-store scheduling barrier keeps
   src++ after the store. The true-space name makes 0x800194C8 a local join. */
