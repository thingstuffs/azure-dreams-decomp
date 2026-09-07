#include "common.h"

extern u8 D_8001A92C;
extern s32 func_8001A7B0(u8);

s32 func_8046F1C8(void) {
    u8 *s0 = &D_8001A92C;

    if (D_8001A92C != 0) {
        do {
            if (func_8001A7B0(*s0) != 0) {
                return 1;
            }
            s0++;
        } while (*s0 != 0);
    }
    return 0;
}
