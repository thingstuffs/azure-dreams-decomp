#include "common.h"

/* Globals accessed directly via %hi/%lo (not $gp small-data); declared with a
 * size > -G (8) so gcc/as emit %hi/%lo rather than $gp-relative access. Only
 * element 0 is touched here; other functions referencing D_80073734 (grepped
 * across asm/nonmatchings/code/*.s) also only ever touch offset 0, so the
 * true size may just be a 4B scalar that happens to fall outside this TU's
 * small-data (-G) window -- declared as int[4] purely to force hi/lo codegen. */
extern int D_80073734[4];

/* Records a level index from 1 through 24, or returns 0xFF if invalid. */
int func_8005A3F0(int level_index) {
    level_index &= 0xFF;
    if ((unsigned)level_index >= 25) return 0xFF;
    if (level_index == 0) return 0xFF;
    D_80073734[0] = level_index;
    return level_index;
}
