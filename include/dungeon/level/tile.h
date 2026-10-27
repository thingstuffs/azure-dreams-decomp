/* Complete resident-engine cohort contract; review pending. */
#ifndef DUNGEON_ENGINE_TILE_MAP_H
#define DUNGEON_ENGINE_TILE_MAP_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/record_ptrs.h"
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "modules/dungeon_engine_tile_map_abi_views.h"
#include "modules/dungeon_engine_tile_map_fragment_b4f0c.h"
#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "dungeon/level.h"

s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);

#endif
