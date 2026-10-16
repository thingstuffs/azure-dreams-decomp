#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80017B98;

/* Passes D_80017B98 to townApplyHalfStepPositionDeltas by address. */
void townApplyGlobalDeltaRecordH(void) {
    townApplyHalfStepPositionDeltas(&D_80017B98);
}
