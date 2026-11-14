#include "common.h"
#include "shared/entity_objects.h"
#include "town/person/motion.h"
#include "town/person.h"
#include "town/person/position.h"
#include "shared/object_index_slots.h"

/* Move coordinates halfway toward the target and advance state when the timer expires. */
void move_coordinates_halfway_toward_target(TownObjectRecord *state, s32 *coords) {
    s32 target;
    s32 value;
    s32 value2;
    u16 timer;

    target = view_reference_entity.x.v;
    value = coords[0];
    coords[0] = value + ((target - value) / 2);
    target = view_reference_entity.y.v;
    value2 = coords[1];
    coords[1] = value2 + ((target - value2) / 2);

    timer = state->timer - 1;
    state->timer = timer;
    if ((s16)timer <= 0) {
        state->handler = copy_view_position_with_height;
        object_index_slots[state->slot].unk_01 = 0;
    }
}
