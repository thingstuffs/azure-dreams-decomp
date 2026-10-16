#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_80017B90;

/* Passes the global pointer D_80017B90 by reference to townApplyPositionOffsetPair. */
void townApplyGlobalPointerDeltasC(void) {
    townApplyPositionOffsetPair(&D_80017B90);
}
