#include "common.h"
#include "town/scene/grid_entry_query.h"
#include "town.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Return whether func_80017354 returns a value other than -1. */
s32 has_matching_grid_entry(s32 grid_y, s32 grid_x) {
    return ~find_entry_index_by_grid_bytes(grid_y, grid_x) != 0;
}
