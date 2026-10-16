#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80017B98;

/* Passes D_80017B98 to townApplyPositionOffsetPair. */
void townApplyGlobalDeltaRecordI(void) {
    townApplyPositionOffsetPair(&D_80017B98);
}
