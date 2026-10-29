#include "common.h"
#include "slus.h"
#include "town/scene/resource.h"

/* Run two setup routines, then call reserve_twch_load with mode 2. */
void reserve_movie_resources_mode_2(void) {
    invalidate_four_sprite_resource_slots();
    load_bin_nametwin();
    reserve_twch_load(2);
}
