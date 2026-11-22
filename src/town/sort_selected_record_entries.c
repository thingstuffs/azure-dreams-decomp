#include "common.h"
#include "town.h"
#include "town/shop/resource_entry_initialization_g01156.h"

#include "slus/sort_rank_81540.h"


/* Sort the currently selected carried or stored item list. */
void sort_selected_record_entries(ItemMenuInputObject *record) {
    sort_entries_by_category(record->lists[record->source_index]);
}
