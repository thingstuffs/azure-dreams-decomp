#include "common.h"

extern s32 ratan2(s32 y, s32 x);
extern s32 rsin(s32 angle);
extern s32 rcos(s32 angle);

s32 func_8003BD84(s32 x, s32 y) {
    s32 ax = (x >= 0) ? x : -x;
    s32 ay = (y >= 0) ? y : -y;

    if (ax >= ay) {
        return (x / rcos(ratan2(y, x))) << 12;
    }
    return (y / rsin(ratan2(y, x))) << 12;
}
