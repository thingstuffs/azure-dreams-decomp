#include "common.h"
#include "m2c_compat.h"
#include "shared/position_views.h"

/* cfail-repair: tf7-phase1-cache-v3 */
   /* arg0 in evaluate_surface_components_c */

/* Evaluate the three signed components stored in the input record. */
s16 evaluate_surface_components_c(SignedPositionView *components) {
    return find_highest_valid_cell_height(components->unk_02, components->unk_06, components->unk_0A);
}
