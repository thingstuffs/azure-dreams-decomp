#include "common.h"
#include "engine/movie.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern unsigned char town_movie_callback_list[16];
extern MovieListNode D_800D42E4;

/* Calls append_list_tail with town_movie_callback_list, & D_800D42E4. */
void append_global_entry_to_linked_list(void) {
    append_list_tail(town_movie_callback_list, &D_800D42E4);
}
