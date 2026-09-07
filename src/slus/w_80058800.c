#include "common.h"

/* memcmp-like byte comparison: returns -1 if n==0, else (int)p1[k]-(int)p2[k] at
   first mismatch (or last byte if all equal, unconditionally re-tested). */
s32 func_80058800(u8 *p1, u8 *p2, s32 n) {
    s32 result;

    if (n == 0) {
        return -1;
    }
    while (--n) {
        if (*p1 != *p2) {
            result = *p1 - *p2;
            return result;
        }
        p1++;
        p2++;
    }
    result = *p1 - *p2;
    return result;
}
