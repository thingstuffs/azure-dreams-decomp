#ifndef SLUS_TOWN_MAP_SELECTION_DATA_H
#define SLUS_TOWN_MAP_SELECTION_DATA_H

#include "common.h"

/* Resident selected town map entry at 0x80082ABC. */
extern u32 town_map_selection;

/* Packed map scene and variant at 0x8006ADD4, the live runtime record +0x18. */
extern s32 map_scene_selector_alias;

#endif
