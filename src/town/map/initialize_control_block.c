#include "town/map/camera.h"
#include "shared/entity_objects.h"

/* Copy the default position and initialize the primary camera callbacks. */
void initialize_control_block(TownCameraState *control) {
    IntVector3 *dst = &town_position_reference_state;
    s32 value;

    town_position_reference_state.x = view_reference_entity.x.v;
    value = view_reference_entity.y.v;
    dst->z = view_reference_entity.z.v;
    dst->y = value;
    control->select_target = set_object_callback_when_active;
    control->override_target = 0;
    initialize_transition_state(control);
}
