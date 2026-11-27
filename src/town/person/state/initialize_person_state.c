#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_node.h"
#include "town/person.h"
#include "town/person/state.h"
#include "town/person/motion.h"
#include "town/person/state_updates.h"





/* Initialize state and copy default values, adjusting the final output value. */
void initialize_person_state(TownObjectRecord *state, ObjectPosition *position) {
    NODE_HEADER(state)->update_callback = update_person_view_and_record;
    fill_position_history();
    state->unk_90 = 0;
    state->state_callback.as_pm = move_person_toward_sample;
    state->sequence_step = 0;
    position->x.w.i = view_reference_entity.x.w.i;
    position->y.w.i = view_reference_entity.y.w.i;
    position->z.w.i = view_reference_entity.z.w.i - get_map_cell_step_size(position);
}
