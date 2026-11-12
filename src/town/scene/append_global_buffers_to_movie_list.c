#include "common.h"
#include "shared/game_work.h"

extern void append_list_tail(void *a0, void *a1);
extern unsigned char town_movie_callback_list[16];
extern unsigned char D_800D4284[16];
/* Passes the two global buffers to append_town_movie_list_node. */
void append_global_buffers_to_movie_list(void)
{
    append_list_tail(&town_movie_callback_list, &D_800D4284);
}
