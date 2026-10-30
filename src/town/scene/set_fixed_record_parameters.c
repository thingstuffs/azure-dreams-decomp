/* Applies fixed position-trace parameters and sets two linked record states. */
/* Complete assigned cohort in retail order; compiled once as one native TU. */
#include "town/scene/set_fixed_record_parameters.h"
#include "town/scene.h"


/* Calls blend_position_and_trace with the fixed parameters (7, 1, 1, 2). */
void set_fixed_record_parameters(void) {
    blend_position_and_trace(7, 1, 1, 2);
}

/* Calls blend_position_and_trace with fixed arguments (7, 1, -1, 2). */
void set_negative_record_parameters(void) {
    blend_position_and_trace(7, 1, -1, 2);
}

/* Set the current record's linked state fields to 0x15 and 0x12. */
void set_current_record_linked_states(void) {
    town_scene_root->position->x = 0x15;
    town_scene_root->position->y = 0x12;
}
