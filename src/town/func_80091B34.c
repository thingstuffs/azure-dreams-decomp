#include "common.h"
#include "m2c_compat.h"

void townApplyUpperLowerBoundaryAdjustmentsFixedPoint(s32, M2C_UNK);                            /* extern */
M2C_UNK func_8008F350();                /* extern */

/* Pass the same value and context to both processing routines. */
void townCallTheSameContextBothProcessingRoutines(s32 value, M2C_UNK context) {
    townApplyUpperLowerBoundaryAdjustmentsFixedPoint(value, context);
    func_8008F350(value, context);
}
