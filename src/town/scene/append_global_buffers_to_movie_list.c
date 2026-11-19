#include "common.h"
#include "slus/data.h"
#include "engine/movie.h"
#include "shared/game_work.h"


extern MovieListNode D_800D4284;
/* Append the first town movie callback node. */
void append_global_buffers_to_movie_list(void)
{
    append_list_tail(&town_movie_callback_list, &D_800D4284);
}
