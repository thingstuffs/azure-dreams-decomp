#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/movie.h"
#include "engine/town.h"
#include "slus/data.h"

extern u8 town_movie_callback_list[];

/* Passes D_8006AE4C and the shared D_800717D0 context to append_town_movie_list_node. */
void queue_town_movie_third(void) {
    append_list_tail(&town_movie_callback_list, &town_movie_descriptor_2);
}
