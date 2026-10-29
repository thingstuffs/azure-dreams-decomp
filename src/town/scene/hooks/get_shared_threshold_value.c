#include "common.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"

extern s32 D_80019438;
/* Returns the current value of D_80019438. */
s32 get_shared_threshold_value(void) {
    return D_80019438;
}
