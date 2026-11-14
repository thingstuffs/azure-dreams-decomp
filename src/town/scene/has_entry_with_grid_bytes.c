#include "town/scene/grid_entry_query.h"
#include "town/scene.h"


/* Return whether func_8001979C produces a value other than -1. */
s32 has_entry_with_grid_bytes(s32 first_input, s32 second_input) {
    return ~find_entry_index_by_grid_bytes(first_input, second_input) != 0;
}
