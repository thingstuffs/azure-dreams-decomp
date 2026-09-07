#include "common.h"

s32 func_8001A58C(s32 arg0) {
    register u8 *p ASM_REG("$3") = (u8 *)0x80010000;

    ASM_KEEP(p);
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
