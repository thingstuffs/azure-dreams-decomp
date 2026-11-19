#ifndef DUNGEON_PLAYER_HELD_ITEM_KIND_DATA_H
#define DUNGEON_PLAYER_HELD_ITEM_KIND_DATA_H

#include "common.h"
#include "shared/dungeon_item_entries.h"

/* Four-byte carried slot. The floor lift fills its fields or copies one complete floor item. */
extern DungeonItemEntry held_item_record;

/* Byte at held_item_record + 1 (0x80081485). */
extern u8 held_item_kind_alias;

#endif
