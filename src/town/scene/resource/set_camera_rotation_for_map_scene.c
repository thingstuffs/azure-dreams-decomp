#include "common.h"
#include "slus/town_map_selection_data.h"
#include "shared/game_work.h"
#include "town/scene/resource.h"


/* Sets the camera X rotation to -0x240 when map_scene_selector_alias is 0x3E000C. */
void set_camera_rotation_for_map_scene(void) {
    GameWork *state = &g_game_work;

    if (map_scene_selector_alias == 0x3E000C) {
        state->view.camera_rotation.parts.camera_rotation_x = -0x240;
    }
}
