#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void append_town_movie_list_node();        /* extern */
extern u8 D_8006AE34[];
extern u8 D_800717D0[];

/* Passes D_8006AE34 and the shared D_800717D0 context to append_town_movie_list_node. */
void queue_town_movie_second(void) {
    append_town_movie_list_node(&D_800717D0, &D_8006AE34);
}
