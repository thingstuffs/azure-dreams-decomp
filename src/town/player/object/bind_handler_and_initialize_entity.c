#include "common.h"
#include "shared/entity.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                      /* extern */

/* Assign the state table, initialize the record, and set its secondary value to -0x40000. */
void bind_handler_and_initialize_entity(BoundEntityHandlerState *state, ObjectPosition *record, void *unused_action_data) {
    state->handler = &adjust_object_motion_at_threshold;
    clear_entity_record_fields(record);
    record->velocity_z = 0xFFFC0000;
}
