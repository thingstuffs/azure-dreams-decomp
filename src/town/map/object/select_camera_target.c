#include "engine/message/data.h"
#include "engine/message.h"
#include "town/map/camera.h"
#include "shared/object_index_slots.h"
#include "shared/object_node.h"
#include "engine/script.h"
#include "town/map/object.h"
#include "town/map.h"

/* Select an override or object position, falling back after nine idle calls. */
void select_camera_target(TownCameraState *object) {
    ScriptController *controller;
    ObjectNodeHeader *selected;
    IntVector3 *value;
    s32 idle_count;
    u8 state_index;

    if (service_script_controller() != 0) {
        controller = &runtime_script_state;
        if (controller->camera_target_slot != 0) {
            object->idle_calls = 0;
        }
        value = object->override_target;
        if (value != 0) {
            object->target = value;
            return;
        }
        state_index = controller->camera_target_slot;
        if ((u32)(state_index - 2) < 0x53U) {
            selected = object_index_slots[controller->camera_target_slot].object;
            if (selected != 0) {
                object->target = (IntVector3 *)selected->position;
                return;
            }
        } else if (state_index == 0) {
            idle_count = object->idle_calls + 1;
            object->idle_calls = idle_count;
            if (idle_count < 9) {
                return;
            }
            object->idle_calls = 9;
        }
        object->target = &town_position_reference_state;
        return;
    } else {
        object->target = &town_position_reference_state;
        object->select_target = enable_camera_target_selection;
        object->override_target = 0;
    }
}
