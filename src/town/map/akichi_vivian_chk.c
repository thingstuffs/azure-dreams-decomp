#include "common.h"
#include "town/map.h"
#include "town/data.h"

/* akichi_vivian_chk: return the vacant-lot Vivian check flag. */
u8 akichi_vivian_chk(void) {
    return town_building_scene_index;
}
