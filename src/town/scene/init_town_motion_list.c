#include "common.h"
#include "town/scene.h"
#include "town/scene/secondary_object_list_g00528.h"

/* Initializes both town_motion_list links to the list sentinel. */
void init_town_motion_list(void) {
    town_motion_list[0] = town_motion_list;
    town_motion_list[1] = town_motion_list;
}
