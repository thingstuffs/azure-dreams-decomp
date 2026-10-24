#include "town/scene.h"
/* Apply global delta record f.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01234 - PR:town/ll34_3e5000_80016000:80017B98.
 */
#include "town/scene/apply_global_delta_record_f_g01234.h"

/* Passes the shared data at D_80017B98 to apply_signed_stat_deltas. */
void apply_global_delta_record_f(void) {
    apply_signed_stat_deltas(&D_80017B98);
}

/* Pass D_80017BA8 to func_80019D60. */
void apply_global_delta_record_g(void) {
    func_80019D60(&D_80017BA8);
}

/* Passes D_80017B98 to apply_half_step_position_deltas by address. */
void apply_global_delta_record_h(void) {
    apply_half_step_position_deltas(&D_80017B98);
}

/* Passes D_80017B98 to apply_position_offset_pair. */
void apply_global_delta_record_i(void) {
    apply_position_offset_pair(&D_80017B98);
}
