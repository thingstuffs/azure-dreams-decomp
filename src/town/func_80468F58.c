#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_80017B90;

/* Passes the address of D_80017B90 to townApplyHalfStepPositionDeltas. */
void townApplyGlobalPointerDeltasB(void) {
    townApplyHalfStepPositionDeltas(&D_80017B90);
}
