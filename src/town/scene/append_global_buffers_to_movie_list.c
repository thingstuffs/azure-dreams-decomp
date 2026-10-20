#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void append_town_movie_list_node(void *a0, void *a1);
extern unsigned char D_800717D0[16];
extern unsigned char D_800D4284[16];
/* Passes the two global buffers to append_town_movie_list_node. */
void append_global_buffers_to_movie_list(void)
{
    append_town_movie_list_node(&D_800717D0, &D_800D4284);
}
