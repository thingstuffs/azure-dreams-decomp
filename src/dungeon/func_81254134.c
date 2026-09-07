#include "common.h"

extern u16 D_80013714[];

s32 func_81254134(void) {
    if (D_80013714[0] & 0x10) {
        return 1;
    }
    return 0;
}
