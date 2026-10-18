#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_target_and_handler_table(void *, s32);                            /* extern */

/* Forward the state and value to initialize_target_and_handler_table. */
void forward_state_value_to_handler_a(void *state, s32 value) {
    initialize_target_and_handler_table(state, value);
}
