#ifndef DUNGEON_ITEM_ACTOR_TARGET_H
#define DUNGEON_ITEM_ACTOR_TARGET_H

#include "common.h"

struct ActorRecord;

/* Actor searches and route-point selection. */
s32 find_entity_slot_by_field_ac(void *target_value);
void *find_adjacent_actor(void *entity, u16 x, u16 y);
s32 select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
u8 *select_item_record_pointer(s32 selector_id);

void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction);

#endif
