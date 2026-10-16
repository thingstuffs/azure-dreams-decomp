#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B9C;

/* Pass the global object D_80017B9C to townApplySignedStatDeltas. */
void townApplyGlobalDeltaRecordJ(void) {
    townApplySignedStatDeltas(&D_80017B9C);
}
