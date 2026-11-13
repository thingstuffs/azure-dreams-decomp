#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"

/* Returns whether either interaction check accepts the fixed ID/type pair 13 and 3. */
s32 check_progress_interaction_accepted(void) {
    s32 result = 0;

    if ((check_callback_record_bytes(13, 3) != 0) ||
        (is_four_arg_result_valid(13, 3) != 0)) {
        result = 1;
    }
    return result;
}
