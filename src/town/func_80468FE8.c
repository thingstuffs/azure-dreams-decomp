#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B94;

/* Passes D_80017B94 to townApplyHalfStepPositionDeltas. */
void townApplyGlobalDeltaRecordD(void) {
    townApplyHalfStepPositionDeltas(&D_80017B94);
}
