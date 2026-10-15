#include "common.h"
#include "shared/game_work.h"

/* Seed the resident dungeon RNG. The SLUS item-category shuffle calls this
 * entry with its saved seed before shuffling category records. */
void func_800A6D98(s32 seed) {
    gameWork.randSeed = seed;
}
