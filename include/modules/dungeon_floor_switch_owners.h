#ifndef DUNGEON_FLOOR_SWITCH_OWNERS_H
#define DUNGEON_FLOOR_SWITCH_OWNERS_H
#include "common.h"
#include "records/Rec_func_8001CE44_arg0.h"
#include "shared/dungeon_item_entries.h"

void choose_random_region_feature(Rec_func_8001CE44_arg0 *region, s32 update_id);
void init_random_floor_item_parameters(DungeonItemEntry *entity_data);
#endif
