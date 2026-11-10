#include "common.h"
#include "town/scene/hooks.h"
#include "town/scene.h"


/* Return whether func_8001DA48 produces a value other than -1. */
s32 is_pair_result_valid(s32 first_input, s32 second_input) {
    return ~find_entry_index_by_grid_bytes(first_input, second_input) != 0;
}
