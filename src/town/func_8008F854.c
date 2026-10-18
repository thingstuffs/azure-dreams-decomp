#include "common.h"
#include "m2c_compat.h"
#include "shared/types3a_types.h"

/* cfail-repair: tf7-phase1-cache-v3 */
   /* arg0 in forward_smallest_surface_x_query */

/* Pass three signed record components to find_smallest_surface_x_across_tiles. */
s16 forward_smallest_surface_x_query(SignedPositionView *record) {
    return find_smallest_surface_x_across_tiles(record->unk_02, record->unk_06, record->unk_0A);
}
