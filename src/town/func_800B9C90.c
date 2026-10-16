#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townClearHalfwordGrid128(s16 *grid);                            /* extern */

/* Clear the grid and initialize its contents. */
void townClearAndInitializeBuildingGrid(s32 grid) {
    townClearHalfwordGrid128(grid);
    townInitializeBuildingSceneObjects(grid);
}
