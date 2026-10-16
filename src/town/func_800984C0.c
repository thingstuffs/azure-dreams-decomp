#include "common.h"

extern s16 dungeonEvaluateSummedPositionMinusYOffset(s32 input_value, s32 value, s32 parameter);
extern s32 D_800D0418;

/* Call dungeonEvaluateSummedPositionMinusYOffset with the input, D_800D0418, and parameter. */
s16 townCallCallee8008C610Global800D0418Parameter(s32 input_value, s32 parameter) {
    return dungeonEvaluateSummedPositionMinusYOffset(input_value, D_800D0418, parameter);
}
