#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B94;

/* Pass the global data at D_80017B94 to townApplySignedStatDeltas. */
void townApplyGlobalDeltaRecordB(void) {
    townApplySignedStatDeltas(&D_80017B94);
}
