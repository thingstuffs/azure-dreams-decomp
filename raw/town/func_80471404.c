#include "common.h"

extern u8 D_8001B218[];

s32 func_80471404(void) {
    if (D_8001B218[5] != 13) {
        goto zero;
    }
    if (D_8001B218[4] != 4) {
        goto zero;
    }
    if (D_8001B218[7] & 0x20) {
        return 1;
    }
zero:
    return 0;
}
