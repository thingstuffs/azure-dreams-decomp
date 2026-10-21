#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/movie.h"
#include "engine/town.h"
#include "slus/data.h"

extern u8 town_movie_callback_list[];

/* Passes D_8006AE7C and the shared D_800717D0 context to append_town_movie_list_node. */
void queue_town_movie_fifth(void) {
    append_town_movie_list_node(&town_movie_callback_list, &town_movie_descriptor_4);
}
