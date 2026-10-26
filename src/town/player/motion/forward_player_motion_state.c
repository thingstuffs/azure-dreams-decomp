#include "common.h"
#include "town/player/scene_action_setup.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_record_with_handler_table(void *, s32, s32);                            /* extern */

/* Forward the state, value, and mode to initialize_record_with_handler_table. */
void forward_player_motion_state(void *state, s32 value, s32 mode) {
    initialize_record_with_handler_table(state, value, mode);
}
