#ifndef SLUS_SORT_RANK_81540_H
#define SLUS_SORT_RANK_81540_H

#include "common.h"
#include "shared/dungeon_item_entries.h"

extern u8 *current_sort_rank_table;
void sort_entries_by_category(DungeonItemEntry **entries);
s32 count_entries_matching_first(DungeonItemEntry **entries);
void stamp_first_matching_entry_ranks(u8 *marks, DungeonItemEntry **entries, s32 match_key);
extern s32 compare_mapped_leading_bytes(u8 **left, u8 **right);

#endif
