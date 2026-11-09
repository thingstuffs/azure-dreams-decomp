#ifndef DUNGEON_FLOOR_SWITCH_OWNERS_H
#define DUNGEON_FLOOR_SWITCH_OWNERS_H
#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_floor.h"

void init_random_floor_item_parameters(DungeonItemEntry *entity_data);
void choose_random_region_feature(DungeonRoom *region, s32 update_id);
#endif
