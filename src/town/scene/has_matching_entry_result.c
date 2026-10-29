#include "common.h"
#include "town/scene.h"

/* Return whether find_entry_index_by_grid_bytes produces a result other than -1. */
s32 has_matching_entry_result(s32 first_value, s32 second_value) {
    return ~find_entry_index_by_grid_bytes(first_value, second_value) != 0;
}
