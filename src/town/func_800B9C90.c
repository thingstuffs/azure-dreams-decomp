#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800B7384(s16 *grid);                            /* extern */

/* Clear the grid and initialize its contents. */
void func_800B73F0(s32 grid) {
    func_800B7384(grid);
    func_800B8E08(grid);
}
