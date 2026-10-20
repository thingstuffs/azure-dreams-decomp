#include "common.h"

extern void get_first_free_four_byte_entry_index_n_1_none_available(void *entry, s32 entry_count);
extern s32 find_target_byte_index_in_list(void);
extern s32 D_800D0728[];

/* sarch_koyaw_free: search for a free entry using the selected capacity. */
void sarch_koyaw_free(void) {
    s32 capacity_index;

    capacity_index = find_target_byte_index_in_list();
    get_first_free_four_byte_entry_index_n_1_none_available((void *)0x80010980, D_800D0728[capacity_index]);
}
