#ifndef DUNGEON_PLAYER_SPECIAL_TABLE_INDEX_G00320_H
#define DUNGEON_PLAYER_SPECIAL_TABLE_INDEX_G00320_H
/* Special table index shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800934E8. */

#include "common.h"
#include "shared/dungeon_item_entries.h"

extern DungeonItemEntry held_item_record;
extern u8 temporary_item_record[];

/* Functions defined in this translation unit. */
s32 find_table_entry_address_index(s32 entry_address);
s32 get_special_table_data_index(s32 dataAddress);

#endif
