#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void set_event11_camera_brightness_2(void) {
    town_scene_root->services->came_bright_set(2);
}
