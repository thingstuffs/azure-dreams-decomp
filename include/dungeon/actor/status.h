#ifndef DUNGEON_ACTOR_STATUS_H
#define DUNGEON_ACTOR_STATUS_H

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity.h"

/* Four status slots shared by actor records and their status-storage views. */
struct Owner_800A48F0;
s16 set_or_clear_actor_status_slot(struct Owner_800A48F0 *owner, s8 id, s8 value);
void advance_status_timers(void *record);

s32 feed_actor_restore_mp(ActorRecord *state, s32 mode, DungeonItemEntry *item);

#endif
