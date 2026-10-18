#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void dispatch_state_callback_by_mode(s32, void *, void *, s32);                            /* extern */

/* Forward the value, context, data, and mode to dispatch_state_callback_by_mode. */
void forward_value_context_data_mode(s32 value, void *context, void *data, s32 mode) {
    dispatch_state_callback_by_mode(value, context, data, mode);
}
