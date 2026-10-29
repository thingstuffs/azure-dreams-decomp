#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

s32 func_800191E8(s32 *);
extern M2C_UNK D_8001AA2E;

/* Return the fallback pointer when the input check is below -47. */
s32 *select_fallback_when_below_threshold(void *input) {
    void *selected_ptr;

    selected_ptr = input;
    if (func_800191E8(input) < -0x2F) {
        selected_ptr = &D_8001AA2E;
    }
    return selected_ptr;
}
