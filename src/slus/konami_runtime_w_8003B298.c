#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void append_town_movie_list_node();        /* extern */
extern u8 D_8006AE64[];
extern u8 D_800717D0[];

/* Passes D_8006AE64 and the shared D_800717D0 context to append_town_movie_list_node. */
void func_8003B298(void) {
    append_town_movie_list_node(&D_800717D0, &D_8006AE64);
}
