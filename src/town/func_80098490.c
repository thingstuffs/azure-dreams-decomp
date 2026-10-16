#include "common.h"

extern s16 townQueryOffsetPositionMinusX(s32 vector, s32 entries, s32 entry_index);
extern s32 D_800D0414;

/* Call townQueryOffsetPositionMinusX with the input, D_800D0414, and parameter. */
s16 townCallCallee8008C570Global800D0414Parameter(s32 input_value, s32 parameter) {
    return townQueryOffsetPositionMinusX(input_value, D_800D0414, parameter);
}
