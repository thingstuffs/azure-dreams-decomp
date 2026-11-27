#include "common.h"
#include "town/scene/record_queries.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern M2C_UNK restaurant_below_threshold_fallback_response;

/* Return the fallback pointer when the input check is below -47. */
s32 *select_fallback_when_below_threshold(void *input) {
    void *selected_ptr;

    selected_ptr = input;
    if (get_current_nested_record_value() < -0x2F) {
        selected_ptr = &restaurant_below_threshold_fallback_response;
    }
    return selected_ptr;
}
