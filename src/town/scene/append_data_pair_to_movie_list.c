#include "shared/game_work.h"

#include "engine/movie.h"
#include "town/scene.h"

struct S_8003AF58_1; void append_list_tail(void *, struct S_8003AF58_1 *);
extern MovieListNode town_movie_callback_list;
extern s8 scene_music_hold;
extern MovieListNode D_800D429C;
/* Pass the town data pair to append_town_movie_list_node and set the shared flag. */
void append_data_pair_to_movie_list(void)
{
    long enabled;
    append_list_tail(&town_movie_callback_list, &D_800D429C);
    enabled = 1;
    scene_music_hold = enabled;
    scene_music_hold = 1;
}
