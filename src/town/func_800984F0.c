#include "common.h"

extern s16 dungeonAdjustSummedVectorByEntryComponent(s32 input_value, s32 value, s32 parameter);
extern s32 D_800D041C;

/* Call dungeonAdjustSummedVectorByEntryComponent with the input, D_800D041C, and parameter. */
s16 townCallCallee8008C6B8Global800D041CParameter(s32 input_value, s32 parameter) {
    return dungeonAdjustSummedVectorByEntryComponent(input_value, D_800D041C, parameter);
}
