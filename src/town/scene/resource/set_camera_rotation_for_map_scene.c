#include "slus/map_state.h"
#include "common.h"
#include "slus/town_map_selection_data.h"
#include "shared/game_work.h"
#include "town/scene/resource.h"


/* Sets the camera X rotation to -0x240 for scene 12, map 62. */
void set_camera_rotation_for_map_scene(void) {
    GameWork *state = &g_game_work;

    if (map_runtime_state.scene_selector == 12 && map_runtime_state.map_index == 62) {
        state->view.camera_rotation.parts.camera_rotation_x = -0x240;
    }
}
