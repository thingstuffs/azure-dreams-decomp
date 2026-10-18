#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void append_town_movie_list_node();        /* extern */
extern u8 D_8006AE1C[];
extern u8 D_800717D0[];

/* Passes D_8006AE1C and the shared D_800717D0 context to append_town_movie_list_node. */
void func_8003B188(void) {
    append_town_movie_list_node(&D_800717D0, &D_8006AE1C);
}
