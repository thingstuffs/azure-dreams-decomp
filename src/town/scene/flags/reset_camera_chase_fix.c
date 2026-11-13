#include "modules/town_ovl_3fe0d0_p00.h"

void reset_camera_chase_fix(void) {
    town_scene_root->services->tcame_chase_fix_reset(0);
}
