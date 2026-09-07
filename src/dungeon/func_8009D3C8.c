#include "common.h"

extern u16 D_80013714;
extern u8 D_800E3D20;

s32 func_800A2B28(void) {
    if (!(D_80013714 & 2) && D_800E3D20) {
        return 1;
    }
    return 0;
}
