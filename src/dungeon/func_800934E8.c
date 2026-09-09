#include "common.h"

s32 func_80098C48(s32 arg0) {
    s32 count = 0x13;
    s8 *ptr = (s8 *)0x80010294;

    do {
        if ((s32)ptr != arg0) {
            count -= 1;
            ptr -= 4;
            continue;
        }
        return (s16)count;
    } while (count >= 0);
    return -1;
}
