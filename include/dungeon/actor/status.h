#ifndef DUNGEON_ACTOR_STATUS_H
#define DUNGEON_ACTOR_STATUS_H

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity.h"

/* Four status slots shared by actor records and their status-storage views. */
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
void advance_status_timers(void *record);

#endif
