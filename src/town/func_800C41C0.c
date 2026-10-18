#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
extern void append_town_movie_list_node();
extern M2C_UNK D_800717D0;
extern s8 D_80080A88;
extern M2C_UNK D_800D429C;
/* Pass the town data pair to append_town_movie_list_node and set the shared flag. */
void append_data_pair_to_movie_list(void)
{
    long enabled;
    append_town_movie_list_node(&D_800717D0, &D_800D429C);
    enabled = 1;
    D_80080A88 = enabled;
    D_80080A88 = 1;
}
