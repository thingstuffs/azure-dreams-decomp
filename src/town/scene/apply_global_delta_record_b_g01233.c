/* Apply global delta record b.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01233 - PR:town/ll34_3e5000_80016000:80017B94.
 */
#include "town/scene/apply_global_delta_record_b_g01233.h"

/* Pass the global data at D_80017B94 to apply_signed_stat_deltas. */
void apply_global_delta_record_b(void) {
    apply_signed_stat_deltas(&D_80017B94);
}

/* Pass D_80017BA4 to func_80019D60. */
void apply_global_delta_record_c(void) {
    func_80019D60(&D_80017BA4);
}

/* Passes D_80017B94 to apply_half_step_position_deltas. */
void apply_global_delta_record_d(void) {
    apply_half_step_position_deltas(&D_80017B94);
}

/* Passes D_80017B94 to apply_position_offset_pair. */
void apply_global_delta_record_e(void) {
    apply_position_offset_pair(&D_80017B94);
}
