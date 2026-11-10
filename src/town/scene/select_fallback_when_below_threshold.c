#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

s32 get_current_nested_record_value(void);
extern M2C_UNK D_8001AA2E;

/* Return the fallback pointer when the input check is below -47. */
s32 *select_fallback_when_below_threshold(void *input) {
    void *selected_ptr;

    selected_ptr = input;
    if (get_current_nested_record_value() < -0x2F) {
        selected_ptr = &D_8001AA2E;
    }
    return selected_ptr;
}
