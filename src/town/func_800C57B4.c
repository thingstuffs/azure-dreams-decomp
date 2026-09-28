#include "common.h"
#include "shared/game_work.h"


/* Return whether the rounded, wrapped angle difference exceeds half the divisions. */
s32 func_800C2F14(s32 angle, s16 divisions) {
    GameWork *angle_data;
    s16 step;
    s32 shifted_divisions;
    s32 division_count;
    s32 distance;
    s16 result;

    angle_data = &gameWork;
    shifted_divisions = divisions << 16;
    division_count = shifted_divisions >> 16;
    result = division_count < 2;
    if (result) {
        return 0;
    }

    result = 0x1000;
    step = (s16)(result / division_count);
    distance = (angle_data->viewAngle + (step / 2) - angle) & 0xFFF;
    distance /= step;
    result = (division_count / 2) < distance;
    return result;
}
