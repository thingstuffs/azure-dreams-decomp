#include "common.h"

/* Compares n bytes at p1 and p2, returning their first difference or -1 when n is zero. */
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
