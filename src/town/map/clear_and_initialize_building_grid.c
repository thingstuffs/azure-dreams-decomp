#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void clear_halfword_grid_128(s16 *grid);                            /* extern */

/* Clear the grid and initialize its contents. */
void clear_and_initialize_building_grid(s32 grid) {
    clear_halfword_grid_128(grid);
    initialize_building_scene_objects(grid);
}
