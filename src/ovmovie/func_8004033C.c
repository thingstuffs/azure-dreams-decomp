#include "modules/ovmovie_game.h"

/* Stores two signed values in the movie state globals. */
void set_movie_strip_offsets(s16 value_d8, s16 value_dc) {
    D_801781D8 = (s32) value_d8;
    D_801781DC = (s32) value_dc;
}
