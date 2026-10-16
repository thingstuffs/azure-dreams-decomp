#include "common.h"

extern s16 dungeonEvaluateSummedVectorMinusBase(s32 input_value, s32 value, s32 parameter);
extern s32 D_800D0410;

/* Call dungeonEvaluateSummedVectorMinusBase with the input, D_800D0410, and parameter. */
s16 townCallCallee8008C4C8Global800D0410Parameter(s32 input_value, s32 parameter) {
    return dungeonEvaluateSummedVectorMinusBase(input_value, D_800D0410, parameter);
}
