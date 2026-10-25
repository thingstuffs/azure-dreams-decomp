#include "modules/dungeon_floor_switch_owners.h"

/* Exact jump_table span; dispatch consumer dungeon/func_8028A4AC. */
const void *const D_80016000[13] __attribute__((aligned(4))) = {
    ((u8 *)choose_random_region_feature + 0x50),
    ((u8 *)choose_random_region_feature + 0x5C),
    ((u8 *)choose_random_region_feature + 0x94),
    ((u8 *)choose_random_region_feature + 0x114),
    ((u8 *)choose_random_region_feature + 0xCC),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104),
    ((u8 *)choose_random_region_feature + 0x104)
};
