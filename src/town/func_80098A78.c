#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC();                         /* extern */
M2C_UNK func_800962B8(s32);                            /* extern */

/* Pass the input to func_800962B8, then townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC. */
void townCallTheCallee800962B8Callee80096208(s32 input_value) {
    func_800962B8(input_value);
    townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC(input_value);
}
