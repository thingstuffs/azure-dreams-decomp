#include "common.h"
#include "town/scene/grid_entry_query.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016A38(s32 grid_y, s32 grid_x);                                /* extern */

/* Return whether func_80016A38 returns a value other than -1. */
s32 check_scene_query_result(s32 grid_y, s32 grid_x) {
    return ~func_80016A38(grid_y, grid_x) != 0;
}
