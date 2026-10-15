#include "common.h"
#include "shared/game_work.h"

/* Restore the saved dungeon RNG seed before the SLUS category shuffle.
 * randSeed is the resident 32-bit RNG state at gameWork + 0x1FC. */
void func_800A6D98(s32 saved_seed) {
    gameWork.randSeed = saved_seed;
}
