#include "common.h"
#include "engine/movie.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern unsigned char town_movie_callback_list[16];
extern MovieListNode D_800D42CC;

/* Passes the global buffer and data address to append_town_movie_list_node. */
void create_familiar_restoration_effect(void) {
    append_list_tail(town_movie_callback_list, &D_800D42CC);
}
