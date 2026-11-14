#include "town/map/camera.h"
#include "engine/script.h"
#include "town/map/object.h"
#include "town/map.h"

/* Switch to the target selector when the script controller is active. */
void enable_camera_target_selection(TownCameraState *object) {
    if (service_script_controller() != 0) {
        object->select_target = select_camera_target;
    }
}
