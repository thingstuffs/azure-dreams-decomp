#include "common.h"
#include "town/player.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the input to correct_fixed_point_value_at_boundaries, then apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc. */
void call_the_callee_800962_b_8_callee_80096208(s32 input_value) {
    correct_fixed_point_value_at_boundaries(input_value);
    apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc((s32 *)(input_value));
}
