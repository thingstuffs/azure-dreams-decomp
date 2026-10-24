#include "town/scene.h"
/* Apply global delta record j.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01235 - PR:town/ll34_3e5000_80016000:80017B9C.
 */
#include "town/scene/apply_global_delta_record_j_g01235.h"

/* Pass the global object D_80017B9C to apply_signed_stat_deltas. */
void apply_global_delta_record_j(void) {
    apply_signed_stat_deltas(&town_scene_delta_words_b);
}

/* Passes D_80017BAC to func_80019D60. */
void apply_global_delta_record_k(void) {
    func_80019D60(&D_80017BAC);
}

/* Pass D_80017B9C to apply_half_step_position_deltas. */
void apply_global_delta_record_l(void) {
    apply_half_step_position_deltas(&town_scene_delta_words_b);
}

/* Passes D_80017B9C to apply_position_offset_pair. */
void apply_global_delta_record_m(void) {
    apply_position_offset_pair(&town_scene_delta_words_b);
}
