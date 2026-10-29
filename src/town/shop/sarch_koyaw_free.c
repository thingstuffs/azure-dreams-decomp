#include "common.h"
#include "town/shop.h"

extern s32 town_record_capacities[];

/* sarch_koyaw_free: search for a free entry using the selected capacity. */
void sarch_koyaw_free(void) {
    s32 capacity_index;

    capacity_index = find_target_byte_index_in_list();
    get_first_free_four_byte_entry_index_n_1_none_available((void *)0x80010980, town_record_capacities[capacity_index]);
}
