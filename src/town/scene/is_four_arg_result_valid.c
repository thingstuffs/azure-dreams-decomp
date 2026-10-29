#include "town/scene/grid_entry_query.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001979C(s32, s32);                                /* extern */

/* Return whether func_8001979C produces a value other than -1. */
s32 is_four_arg_result_valid(s32 first_input, s32 second_input) {
    return ~func_8001979C(first_input, second_input) != 0;
}
