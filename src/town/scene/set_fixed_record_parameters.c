/* Complete assigned cohort in retail order; compiled once as one native TU. */
#include "town/scene/set_fixed_record_parameters.h"
#include "town/scene/set_fixed_record_parameters.h"

/* extern */

/* Calls blend_position_and_trace with the fixed parameters (7, 1, 1, 2). */
void set_fixed_record_parameters(void) {
    blend_position_and_trace(7, 1, 1, 2);
}
#include "town/scene/set_fixed_record_parameters.h"

/* extern */

/* Calls blend_position_and_trace with fixed arguments (7, 1, -1, 2). */
void set_negative_record_parameters(void) {
    blend_position_and_trace(7, 1, -1, 2);
}
#include "town/scene/set_fixed_record_parameters.h"

/* Set the current record's linked state fields to 0x15 and 0x12. */
void set_current_record_linked_states(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x15;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x12;
}
