#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void set_event09_camera_brightness_5(void) {
    town_scene_root->services->came_bright_set(5);
}
