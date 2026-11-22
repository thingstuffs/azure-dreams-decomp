#include "slus/sort_rank_81540.h"
#include "slus.h"
#include "sdk/memory.h"

extern s32 compare_record_sort_weights(void *a0, void *a1);

/* Sorts entries by category, then orders each group using discovery ranks from the original list. */
void sort_entries_by_category(DungeonItemEntry **entries) {
    DungeonItemEntry *original_entries[0x40];
    u8 discovery_ranks[0x80];
    s32 count;
    s32 entry_category;
    s32 group_category;
    DungeonItemEntry **group;
    u8 *work_buf; /* s1: copy then loop work */
    DungeonItemEntry **saved_entries;
    u8 *rank_table;

    rank_table = discovery_ranks;
    current_sort_rank_table = rank_table;
    group = entries;
    count = count_pointer_list_entries((void **)entries);
    saved_entries = original_entries;
    memcpy(saved_entries, group, count * 4);
    saved_entries[count] = 0;
    sort_with_comparator(group, count, 4, compare_record_sort_weights);
    group_category = 0;
    if (*group != 0) {
        work_buf = rank_table;
next_group:
        if (group != 0) {
            entry_category = (*group)->kind;
            if (entry_category != group_category) {
                group_category = entry_category;
                bzero(work_buf, 0x80);
                count = count_entries_matching_first(group);
                stamp_first_matching_entry_ranks(work_buf, original_entries, group_category);
                sort_with_comparator(group, count, 4, compare_mapped_leading_bytes);
                group = group + count;
            }
            if (*group != 0) {
                goto next_group;
            }
        }
    }
}
