#include "common.h"

extern u8 town_building_scene_index;

/* akichi_vivian_chk: return the vacant-lot Vivian check flag. */
u8 akichi_vivian_chk(void) {
    return town_building_scene_index;
}
