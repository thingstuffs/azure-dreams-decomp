#include "common.h"
#include "town/scene/grid_entry_query.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80017354();                                /* extern */

/* Return whether func_80017354 returns a value other than -1. */
s32 has_matching_grid_entry(void) {
    return ~func_80017354() != 0;
}
