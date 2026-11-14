#include "common.h"
#include "town/shop.h"
#include "town/data.h"

/* sarch_koyaw_free: search for a free entry using the selected capacity. */
void sarch_koyaw_free(void) {
    s32 capacity_index;

    capacity_index = find_target_index_in_list();
    find_free_entry_index((void *)0x80010980, town_record_capacities[capacity_index]);
}
