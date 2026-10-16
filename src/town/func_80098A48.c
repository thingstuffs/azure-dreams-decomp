#include "common.h"
#include "m2c_compat.h"

void townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC(s32);                            /* extern */
M2C_UNK func_800962B8();                         /* extern */

/* Pass the input to townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC, then func_800962B8. */
void townCallTheCallee80096208Callee800962B8(s32 input_value) {
    townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC(input_value);
    func_800962B8(input_value);
}
