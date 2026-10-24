#include "common.h"
#include "town/scene/grid_entry_query.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CA8(s32 grid_y, s32 grid_x);                                /* extern */

/* Returns whether func_80018CA8 returns a value other than -1. */
s32 is_result_valid(s32 grid_y, s32 grid_x) {
    return func_80018CA8(grid_y, grid_x) != -1;
}
