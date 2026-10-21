#include "common.h"
#include "engine/resource.h"
#include "sdk/libgte.h"

/* Estimates vector length using its dominant component and angle. */
s32 runtime_estimate_vector_length(s32 x, s32 y) {
    s32 abs_x = (x >= 0) ? x : -x;
    s32 abs_y = (y >= 0) ? y : -y;

    if (abs_x >= abs_y) {
        return (x / rcos(ratan2(y, x))) << 12;
    }
    return (y / rsin(ratan2(y, x))) << 12;
}
