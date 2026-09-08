#include "common.h"

s32 func_8001A58C(s32 arg0) {
    u8 *p = (u8 *)0x80010000;

    ASM_KEEP(p);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (p[0x7BC8] != 0) {
        p += 0x7BC8;
        do {
            if (arg0 == *p) {
                return 1;
            }
            p++;
        } while (*p != 0);
    }
    return 0;
}
