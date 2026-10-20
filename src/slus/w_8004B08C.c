#include "slus/sort_rank_81540.h"

typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

extern s32 count_pointer_list_entries(void **ptr);
extern void forward_selection_sort_request(void *base, s32 count, s32 size, void *compar);
extern s32 table_count_consecutive_pointer_entries_whose_target_byte_matches_first_target_byte(S_8004AFE8 **ptr);
extern void stamp_first_matching_entry_ranks(u8 *ptr, S_8004AFE8 **entries, s32 category);
extern void *memcpy(void *dst, void *src, s32 n);
extern void bzero(void *p, s32 n);
extern s32 table_handle_compares_two_records_subtracting_key_indexed_table_values(void *a0, void *a1);

/* Sorts entries by category, then orders each group using discovery ranks from the original list. */
void sort_entries_by_category(S_8004AFE8 **entries) {
    S_8004AFE8 *original_entries[0x40];
    u8 discovery_ranks[0x80];
    s32 count;
    s32 entry_category;
    s32 group_category;
    S_8004AFE8 **group;
    u8 *work_buf; /* s1: copy then loop work */
    u8 * work_buf_2;
    u8 *rank_table;

    rank_table = discovery_ranks;
    current_sort_rank_table = rank_table;
    group = entries;
    count = count_pointer_list_entries((void **)entries);
    work_buf_2 = (u8 *)original_entries;
    memcpy(work_buf_2, group, count * 4);
    ((S_8004AFE8 **)work_buf_2)[count] = 0;
    forward_selection_sort_request(group, count, 4, table_handle_compares_two_records_subtracting_key_indexed_table_values);
    group_category = 0;
    if (*group != 0) {
        work_buf = rank_table;
next_group:
        if (group != 0) {
            entry_category = (*group)->unk1;
            if (entry_category != group_category) {
                group_category = entry_category;
                bzero(work_buf, 0x80);
                count = table_count_consecutive_pointer_entries_whose_target_byte_matches_first_target_byte(group);
                stamp_first_matching_entry_ranks(work_buf, original_entries, group_category);
                forward_selection_sort_request(group, count, 4, compare_mapped_leading_bytes);
                group = group + count;
            }
            if (*group != 0) {
                goto next_group;
            }
        }
    }
}
