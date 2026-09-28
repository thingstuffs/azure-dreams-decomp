#include "common.h"
#include "shared/game_work.h"

/* Advances the random seed and returns a 15-bit random value. */
s32 func_800A6D30(void) {
    u32 next_seed;

    next_seed = (((u32)gameWork.randSeed) * 0x41C64E6D) + 0x3039;
    gameWork.randSeed = next_seed;
    return (next_seed >> 0x10) & 0x7FFF;
}
