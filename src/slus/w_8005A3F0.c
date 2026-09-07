#include "common.h"

/* Globals accessed directly via %hi/%lo (not $gp small-data); declared with a
 * size > -G (8) so gcc/as emit %hi/%lo rather than $gp-relative access. Only
 * element 0 is touched here; other functions referencing D_80073734 (grepped
 * across asm/nonmatchings/code/*.s) also only ever touch offset 0, so the
 * true size may just be a 4B scalar that happens to fall outside this TU's
 * small-data (-G) window -- declared as int[4] purely to force hi/lo codegen. */
extern int D_80073734[4];

/* Validates a level/index byte argument: masks it to a byte, and if it falls
 * in the valid range 1..24 records it into D_80073734[0] and returns it
 * as-is; otherwise returns 0xFF as an "invalid" sentinel. */
int func_8005A3F0(int a0) {
    a0 &= 0xFF;
    if ((unsigned)a0 >= 25) return 0xFF;
    if (a0 == 0) return 0xFF;
    D_80073734[0] = a0;
    return a0;
}
