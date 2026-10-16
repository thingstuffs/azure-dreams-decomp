#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeTargetAndHandlerTable(void *, s32);                            /* extern */

/* Forward the state and value to townInitializeTargetAndHandlerTable. */
void townForwardStateValueToHandlerA(void *state, s32 value) {
    townInitializeTargetAndHandlerTable(state, value);
}
