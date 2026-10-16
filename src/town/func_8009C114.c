#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeRecordWithHandlerTable(void *, s32, s32);                            /* extern */

/* Forward the state, value, and mode to townInitializeRecordWithHandlerTable. */
void townForwardPlayerMotionState(void *state, s32 value, s32 mode) {
    townInitializeRecordWithHandlerTable(state, value, mode);
}
