#include "town/map/camera.h"
#include "shared/entity_objects.h"
#include "town/map.h"

/* Copy the default position and initialize the primary camera callbacks. */
void init_town_camera_chase_state(TownCameraState *control) {
    IntVector3 *dst = &town_position_reference_state;
    s32 value;

    town_position_reference_state.x = view_reference_entity.x.v;
    value = view_reference_entity.y.v;
    dst->z = view_reference_entity.z.v;
    dst->y = value;
    control->select_target = enable_camera_target_selection;
    control->override_target = 0;
    initialize_midpoint_tracking(control);
}
