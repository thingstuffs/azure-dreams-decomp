#include "common.h"

extern u8 D_8006DE24[];

u8 func_800A3820(s16 arg0) {
    int i = arg0 * 0x14;
    return D_8006DE24[i + 0x13];
}
