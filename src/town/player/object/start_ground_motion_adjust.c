#include "common.h"
#include "shared/entity.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                      /* extern */

/* Assign the state table, initialize the record, and set its secondary value to -0x40000. */
void start_ground_motion_adjust(BoundEntityHandlerState *state, ObjectPosition *record, void *unused_action_data) {
    state->handler = &adjust_object_motion_at_threshold;
    clear_object_velocity(record);
    record->velocity_z = 0xFFFC0000;
}
