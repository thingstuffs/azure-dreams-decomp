#include "town/map/camera.h"
#include "shared/object_index_slots.h"

extern s32 runtime_script_state[];
extern s32 service_script_controller(void);

typedef struct CameraObjectPosition {
    u8 pad_00[8];
    IntVector3 *position;
} CameraObjectPosition;

/* Select an override or object position, falling back after nine idle calls. */
void select_object_value_with_idle_fallback(TownCameraState *object) {
    u8 *state;
    CameraObjectPosition *selected;
    IntVector3 *value;
    s32 idle_count;
    u8 state_index;

    if (service_script_controller() != 0) {
        state = (u8 *)runtime_script_state;
        if (state[1] != 0) {
            object->idle_calls = 0;
        }
        value = object->override_target;
        if (value != 0) {
            object->target = value;
            return;
        }
        state_index = state[1];
        if ((u32)(state_index - 2) < 0x53U) {
            selected = object_index_slots[state[1]].object;
            if (selected != 0) {
                object->target = selected->position;
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
        object->select_target = set_object_callback_when_active;
        object->override_target = 0;
    }
}
