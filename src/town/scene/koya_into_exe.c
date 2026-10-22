#include "common.h"
#include "engine/movie.h"
#include "m2c_compat.h"

extern unsigned char town_movie_callback_list[16];
extern MovieListNode D_800D4398;

/* Handle the koya_into_exe script call. */
void koya_into_exe(void) {
    append_list_tail(town_movie_callback_list, &D_800D4398);
}
