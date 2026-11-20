#include "slus/map_state.h"
#include "common.h"
#include "slus/town_map_selection_data.h"
#include "m2c_compat.h"
#include "engine/movie.h"
#include "dungeon/system.h"

extern M2C_UNK D_800FC428;

/* Upload the movie pixels for scene 12, map 19. */
void upload_town_movie_pixels(void) {
    if (map_runtime_state.scene_selector == 12 && map_runtime_state.map_index == 19) {
        upload_pixel_rectangle(0x360, 0x100, 0x20, 0x80, &D_800FC428);
    }
}
