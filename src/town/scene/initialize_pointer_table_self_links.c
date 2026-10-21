#include "common.h"

extern void *town_motion_list[];

/* Sets the first two pointers in D_800FE490 to the array itself. */
void initialize_pointer_table_self_links(void) {
    town_motion_list[0] = town_motion_list;
    town_motion_list[1] = town_motion_list;
}
