#include "town/map/camera.h"
#include "engine/script.h"
#include "town/map/object.h"

/* Switch to the target selector when the script controller is active. */
void set_object_callback_when_active(TownCameraState *object) {
    if (service_script_controller() != 0) {
        object->select_target = select_object_value_with_idle_fallback;
    }
}
