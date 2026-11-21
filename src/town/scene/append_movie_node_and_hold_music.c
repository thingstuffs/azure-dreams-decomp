#include "shared/movie_list.h"
#include "slus/data.h"
#include "slus/gp_d92c_owned.h"
#include "shared/game_work.h"

#include "engine/movie.h"
#include "town/scene.h"

extern MovieListNode D_800D429C;
/* Pass the town data pair to append_town_movie_list_node and set the shared flag. */
void append_movie_node_and_hold_music(void)
{
    long enabled;
    append_list_tail(&town_movie_callback_list, &D_800D429C);
    enabled = 1;
    scene_music_hold = enabled;
    scene_music_hold = 1;
}
