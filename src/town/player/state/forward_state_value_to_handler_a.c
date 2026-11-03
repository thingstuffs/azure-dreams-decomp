#include "common.h"
#include "m2c_compat.h"
#include "town/player/state.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_target_and_handler_table(void *, ObjectPosition *);                            /* extern */

/* Forward the state and value to initialize_target_and_handler_table. */
void forward_state_value_to_handler_a(void *state, ObjectPosition *position) {
    initialize_target_and_handler_table(state, position);
}
