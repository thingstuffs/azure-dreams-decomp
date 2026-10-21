/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_MENU_EFFECTS_H
#define DUNGEON_ENGINE_MENU_EFFECTS_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/entity_height_offsets.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"

ObjectNodeHeader *allocate_flagged_object_node(int flags);
#endif
