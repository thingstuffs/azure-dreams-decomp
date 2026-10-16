#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townDispatchStateCallbackByMode(s32, void *, void *, s32);                            /* extern */

/* Forward the value, context, data, and mode to townDispatchStateCallbackByMode. */
void townForwardValueContextDataMode(s32 value, void *context, void *data, s32 mode) {
    townDispatchStateCallbackByMode(value, context, data, mode);
}
