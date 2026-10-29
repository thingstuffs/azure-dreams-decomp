#include "common.h"
#include "town/scene.h"

extern void *town_motion_list[];

/* Initializes both town_motion_list links to the list sentinel. */
void initialize_pointer_table_self_links(void) {
    town_motion_list[0] = town_motion_list;
    town_motion_list[1] = town_motion_list;
}
