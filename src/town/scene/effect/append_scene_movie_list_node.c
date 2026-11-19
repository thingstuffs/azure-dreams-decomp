#include "common.h"
#include "slus/data.h"
#include "engine/movie.h"
#include "m2c_compat.h"
#include "town/scene/effect.h"

extern MovieListNode D_800D42CC;

/* Appends this scene's movie list node to the tail of town_movie_callback_list. */
void append_scene_movie_list_node(void) {
    append_list_tail(&town_movie_callback_list, &D_800D42CC);
}
