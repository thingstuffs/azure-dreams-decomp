#include "common.h"
#include "slus/gp_d92c_owned.h"
#include "m2c_compat.h"
#include "engine/movie.h"
#include "engine/scene.h"
#include "town/scene.h"
extern u32 town_scene_resource_descriptor[2];

/* town_movie3_call: Clear the shared flag and invoke the movie setup routines. */
void town_movie3_call(void) {
    scene_music_hold = 0;
    play_movie_with_fixed_display_flag(0x14, 0x304);
    file_load_com(town_scene_resource_descriptor);
}
