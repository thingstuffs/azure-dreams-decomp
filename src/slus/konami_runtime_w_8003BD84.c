#include "common.h"

extern s32 ratan2(s32 y, s32 x);
extern s32 rsin(s32 angle);
extern s32 rcos(s32 angle);

/* Estimates vector length using its dominant component and angle. */
s32 func_8003BD84(s32 x, s32 y) {
    s32 abs_x = (x >= 0) ? x : -x;
    s32 abs_y = (y >= 0) ? y : -y;

    if (abs_x >= abs_y) {
        return (x / rcos(ratan2(y, x))) << 12;
    }
    return (y / rsin(ratan2(y, x))) << 12;
}
