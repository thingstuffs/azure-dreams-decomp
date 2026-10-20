#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void append_town_movie_list_node();        /* extern */
extern u8 town_movie_descriptor_5[];
extern u8 town_movie_callback_list[];

/* Passes D_8006AEAC and the shared D_800717D0 context to append_town_movie_list_node. */
void queue_town_movie_sixth(void) {
    append_town_movie_list_node(&town_movie_callback_list, &town_movie_descriptor_5);
}
