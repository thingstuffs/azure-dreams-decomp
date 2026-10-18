#include "common.h"
#include "shared/game_work.h"

/* Restore the saved dungeon RNG seed before the SLUS category shuffle.
 * randSeed is the resident 32-bit RNG state at g_game_work + 0x1FC. */
void func_800A6D98(s32 saved_seed) {
    g_game_work.randSeed = saved_seed;
}
