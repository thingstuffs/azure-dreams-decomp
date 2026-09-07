#include "common.h"

typedef struct {
    u8 pad[0x1FC];
    u32 rngSeed;
} S_800A15D0_D80083160;

extern S_800A15D0_D80083160 D_80083160;

s32 func_800A6D30(void) {
    u32 temp_v0;

    temp_v0 = (D_80083160.rngSeed * 0x41C64E6D) + 0x3039;
    D_80083160.rngSeed = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}
