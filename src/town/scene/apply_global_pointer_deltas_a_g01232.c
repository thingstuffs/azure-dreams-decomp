/* Apply global pointer deltas a.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01232 - PR:town/ll34_3e5000_80016000:80017B90.
 */
#include "town/scene/apply_global_pointer_deltas_a_g01232.h"

/* Passes the global pointer's address to apply_signed_stat_deltas. */
void apply_global_pointer_deltas_a(void) {
    apply_signed_stat_deltas(&D_80017B90);
}

/* Pass D_80017BA0 to func_80019D60. */
void apply_global_delta_record_a(void) {
    func_80019D60(&D_80017BA0);
}

/* Passes the address of D_80017B90 to apply_half_step_position_deltas. */
void apply_global_pointer_deltas_b(void) {
    apply_half_step_position_deltas(&D_80017B90);
}

/* Passes the global pointer D_80017B90 by reference to apply_position_offset_pair. */
void apply_global_pointer_deltas_c(void) {
    apply_position_offset_pair(&D_80017B90);
}
