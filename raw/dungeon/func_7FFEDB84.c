#include "common.h"

s32 func_8008B2E4(s32 arg0) {
    register s32 *p ASM_REG("$3") = (s32 *)0x800D0000;

    ASM_KEEP(p);
    if (p[-0x1E9] != 0) {
        p += -0x1E9;
        do {
            if (arg0 == *p) {
                return 1;
            }
            p++;
        } while (*p != 0);
    }
    return 0;
}
