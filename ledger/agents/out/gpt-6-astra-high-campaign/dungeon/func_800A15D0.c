#include "common.h"

typedef struct {
    u8 pad[0x1FC];
    u32 rngSeed;
} S_800A15D0_D80083160;

extern S_800A15D0_D80083160 D_80083160;

/* Advances the random seed and returns a 15-bit random value. */
s32 func_800A6D30(void) {
    u32 next_seed;

    next_seed = (D_80083160.rngSeed * 0x41C64E6D) + 0x3039;
    D_80083160.rngSeed = next_seed;
    return (next_seed >> 0x10) & 0x7FFF;
}
