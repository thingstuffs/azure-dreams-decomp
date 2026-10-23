#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/movie.h"
#include "engine/town.h"
#include "slus/data.h"

extern u8 town_movie_callback_list[];

/* Appends town_movie_descriptor_0 to town_movie_callback_list. */
void queue_town_movie_first(void) {
    append_list_tail(&town_movie_callback_list, &town_movie_descriptor_0);
}
