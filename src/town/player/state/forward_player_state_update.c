#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void update_player_global_state(void *, s32, s32);                            /* extern */

/* Forward the object and values to update_player_global_state. */
void forward_player_state_update(void *object, s32 value_1, s32 value_2) {
    update_player_global_state(object, value_1, value_2);
}
