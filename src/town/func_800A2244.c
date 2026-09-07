#include "common.h"

extern s32 D_8001029C[];

s32 func_8009F9A4(void) {
    s32 *ptr;
    s32 count;

    do { count = 0; } while (0);
    ptr = D_8001029C;
loop:
    if (*ptr != 0) {
        count++;
        ptr++;
        if (count < 20) {
            goto loop;
        }
    }
    return count;
}
